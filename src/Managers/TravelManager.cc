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

            setMessageAndNotify("Using special move!");
            pp->resetCooldown();
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
                setMessageAndNotify("Moving " + args[0]);
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
            ostringstream items;
            int index = 0;
            for (auto equip : pp->currentEquipables())
            {
                items << index << " - " << equip->getName() << endl;
                index++;
            }

            for (auto pots : pp->currentConsumables())
            {
                items << index << " - " << pots->getName() << endl;
                index++;
            }

            setMessageAndNotify(items.str());
            break;
        }
        case 'U':
        {
            if (args.size() != 1)
            {
                setMessageAndNotify("Invalid Command");
                break;
            }
            unsigned int itemIndex = 0;
            try
            {
                itemIndex = stoi(args[0]);
            }
            catch (const invalid_argument &e)
            {
                setMessageAndNotify("Invalid Item");
                break;
            }
            if (itemIndex >= pp->currentEquipables().size() + pp->currentConsumables().size())
            {
                setMessageAndNotify("Invalid Item");
                break;
            }
            shared_ptr<Item> item;
            if (itemIndex < pp->currentEquipables().size())
            {
                item = pp->currentEquipables()[itemIndex];
                pp->equipEquipable(pp, item->getName());
            }
            else
            {
                item = pp->currentConsumables()[itemIndex - pp->currentEquipables().size()];
                pp->consumeConsumable(pp,
                                      item->getName());
            }
            string info = "Player used item " + item->getName() + " on themselves.";
            setMessageAndNotify(info);
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
            while (!toExit && !onEnemies())
            {
                char cmd;
                vector<string> args;
                setMessageAndNotify("Input Command (M, A, L, P, D, U)");
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
                    if (auto pp = player.lock())
                    {
                        ostringstream moves;
                        moves << "Possible moves: " << endl;
                        vector<pair<int, int>> possible = pp->specialMoves();
                        for (auto move : possible)
                        {
                            moves << "(" << move.first << "," << move.second << ")" << endl;
                        }
                        setMessageAndNotify(moves.str());
                    }
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
                    string index;
                    cin >> index;
                    args.emplace_back(index);
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

bool TravelManager::onEnemies() const
{
    if (auto mp = map.lock())
    {
        if (auto pp = player.lock())
        {
            for (auto enem : (mp->tile(pp->getPosition())).getEnemies())
            {
                if (enem->getHealth() > 0)
                    return true;
            }
        }
    }
    return false;
}