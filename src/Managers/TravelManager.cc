#include "TravelManager.h"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <memory>

#include "../ADTs/Command/Command.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Item/Item.h"
#include "../ADTs/Map/Map.h"
#include "../ADTs/Map/Tile.h"

using namespace std;

TravelManager::TravelManager(shared_ptr<Map> map, shared_ptr<Player> player)
    : map{map}, player{player} {}

void TravelManager::makeMove(const Command &cmd)
{
    if (auto pp = player.lock())
    {
        vector<string> args = cmd.getArgs();
        switch (cmd.getCommand())
        {
        case 'T':
        {
            if (args.size() != 2)
            {
                setMessageAndNotify("Invalid Command");
                return;
            }
            pair<int, int> coords;
            try
            {
                coords.first = stoi(args[0]);
                coords.second = stoi(args[1]);
            }
            catch (const std::invalid_argument &e)
            {
                setMessageAndNotify("Invalid location for special move");
                return;
            }

            if (!pp->specialReady())
            {
                setMessageAndNotify("Special on cooldown!");
                return;
            }

            if (!pp->useSpecial(coords))
            {
                setMessageAndNotify("Invalid location for special move");
                return;
            }
        }
        case 'M':
        {
            if (args.size() != 1 || !pp->checkMove(args[0].at(0)))
            {
                setMessageAndNotify("Invalid Command");
                return;
            }

            pp->makeMove(args[0].at(0));
        }
        case 'P':
        {
            // TO DO
        }
        case 'L':
        {
            stringstream desc;
            for (auto equip : pp->currentEquipables())
            {
                desc << equip->getName() << endl;
            }
            for (auto pots : pp->currentConsumables())
            {
                desc << pots->getName() << endl;
            }
            setMessageAndNotify(desc.str());
            return;
        }
        case 'U':
        {
            if (args.size() != 1)
            {
                setMessageAndNotify("Invalid Command");
                return;
            }
            shared_ptr<Item> item = nullptr;
            string name = args[0];
            for (auto equip : pp->currentEquipables())
            {
                if (equip != nullptr && equip->getName() == name)
                {
                    item = equip;
                    break;
                }
            }
            if (item == nullptr)
            {
                for (auto pots : pp->currentConsumables())
                {
                    if (pots != nullptr && pots->getName() == name)
                    {
                        item = pots;
                        break;
                    }
                }
            }
            if (item == nullptr)
            {
                setMessageAndNotify("Invalid Command");
                return;
            }
            //TODO
            //player->useItem(player, item);
        }
        }
    }
}

void TravelManager::startTravel()
{
    toBattle = false;
    runTravel();
}

void TravelManager::runTravel()
{
    if (auto mp = map.lock())
    {
        if (auto pp = player.lock())
        {
            while (!((mp->tile(pp->getPosition())).getEnemies().size() == 0))
            {
                char cmd;
                vector<string> args;
                cin >> cmd;
                switch (cmd)
                {
                case 'M':
                {
                    setMessageAndNotify("Input Direction (N,S,E,W)");
                    string dir;
                    cin >> dir;
                    args.emplace_back(dir);
                    break;
                }
                case 'A':
                {
                    setMessageAndNotify("Input Location (x,y)");
                    string x, y;
                    cin >> x >> y;
                    args.emplace_back(x);
                    args.emplace_back(y);
                    break;
                }
                case 'P':
                {
                    break;
                }
                case 'L':
                case 'U':
                {
                    setMessageAndNotify("Input Item");
                    string name;
                    getline(cin, name);
                    args.emplace_back(name);
                    break;
                }
                }

                Command fullCmd(cmd, args);

                makeMove(fullCmd);
            }
            setMessageAndNotify("Enemy encountered! Starting battle!");
            toBattle = true;
        }
    }
}

const weak_ptr<Map> TravelManager::getMap() const { return map; }
