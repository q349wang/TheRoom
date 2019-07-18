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
    : Subject{}, map{map}, player{player} {}

TravelManager::~TravelManager() {}

void TravelManager::makeMove(const Command &cmd)
{
    if (auto pp = player.lock())
    {
        vector<string> args = cmd.getArgs();
        switch (cmd.getCommand())
        {
        case 'A':
        {
            if (args.size() != 2)
            {
                setMessageAndNotify("Invalid Command");
                break;
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
                break;
            }

            if (!pp->useSpecial(coords))
            {
                setMessageAndNotify("Invalid location for special move");
                break;
            }
        }
        case 'M':
        {
            if (args.size() != 1 || !pp->checkMove(args[0].at(0)))
            {
                setMessageAndNotify("Invalid Command");
                break;
            }

            pp->makeMove(args[0].at(0));
            pp->decreaseCooldown();
            if (auto mp = map.lock())
            {
                if (mp->checkExit(pp->getPosition()))
                {
                    setMessageAndNotify("Found exit. Exiting level");
                    toExit = true;
                    break;
                }
                mp->moveEnemies();
            }
            break;
        }
        case 'P':
        {
            vector<shared_ptr<Item>> pickedUp = pp->pickUpItems();
            ostringstream msg;
            msg << "Picked up:\n";
            for (auto item : pickedUp)
            {
                msg << item->getName() << "\n";
            }
            setMessageAndNotify(msg.str());
            break;
        }
        case 'D':
        {
            if (args.size() != 1)
            {
                setMessageAndNotify("Invalid Command");
                break;
            }
            bool dropped = pp->dropItem(args[0]);
            if (dropped)
            {
                setMessageAndNotify("Dropped item: " + args[0]);
            }
            else
            {
                setMessageAndNotify("Could not find item");
            }
            break;
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
            break;
        }
        case 'U':
        {
            if (args.size() != 1)
            {
                setMessageAndNotify("Invalid Command");
                break;
            }
            shared_ptr<Item> item = nullptr;
            string name = args[0];
            for (auto equip : pp->currentEquipables())
            {
                if (equip != nullptr && equip->getName() == name)
                {
                    item = equip;
                    pp->equipEquipable(pp, item->getName());
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
                        pp->consumeConsumable(pp, item->getName());
                        break;
                    }
                }
            }
            if (item == nullptr)
            {
                setMessageAndNotify("Invalid Command");
                break;
            }
            break;
        }
        }
    }
}

void TravelManager::startTravel()
{
    toExit = false;
    toBattle = false;
    runTravel();
}

void TravelManager::runTravel()
{
    if (auto mp = map.lock())
    {
        if (auto pp = player.lock())
        {
            while (!toExit &&
                   !((mp->tile(pp->getPosition())).getEnemies().size() == 0))
            {
                char cmd;
                vector<string> args;
                cin >> cmd;
                switch (cmd)
                {
                    // Move in a specific direction
                case 'M':
                {
                    setMessageAndNotify("Input Direction (N,S,E,W)");
                    string dir;
                    cin >> dir;
                    args.emplace_back(dir);
                    break;
                }
                // Use ability to move to location
                case 'A':
                {
                    setMessageAndNotify("Input Location (x,y)");
                    string x, y;
                    cin >> x >> y;
                    args.emplace_back(x);
                    args.emplace_back(y);
                    break;
                }
                // List items that you have
                case 'L':
                // Pick up item
                case 'P':
                {
                    break;
                }
                // Drop item
                case 'D':
                // Use item on self
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
            if (!toExit)
            {
                setMessageAndNotify("Enemy encountered! Starting battle!");
                toBattle = true;
            }
        }
    }
}

const weak_ptr<Map> TravelManager::getMap() const { return map; }

bool TravelManager::isExiting() const { return toExit; }