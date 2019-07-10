#include "TravelManager.h"
#include <iostream>

#include "../ADTs/Command/Command.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Map/Map.h"

using namespace std;

TravelManager::TravelManager(Map* map, Player* player)
    : player{player}, map{map} {}

void TravelManager::makeMove(const Command& cmd) {
    vector<string> args = cmd.getArgs();
    switch (cmd.getCommand()) {
        case 'D': {
            if (player->getHero() != UNIMPLEMENTED) {
                setMessageAndNotify("Invalid Command");
                return;
            }

            player->useAbility(args);
        }
        case 'T': {
            if (player->getHero() != UNIMPLEMENTED) {
                setMessageAndNotify("Invalid Command");
                return;
            }

            player->useAbility(args);
        }
        case 'M': {
            if (args.size() != 1 || !player->checkMove(args[0])) {
                setMessageAndNotify("Invalid Command");
                return;
            }

            player->move(args[0]);
        }
        case 'P': {
            // TO DO
        }
        case 'L': {
            // TO DO
        }
        case 'U': {
            if (args.size() != 1 || !player->checkMove(args[0])) {
                setMessageAndNotify("Invalid Command");
                return;
            }
            Item* item = nullptr;
            string name = args[0];
            for (auto equip : player->currentEquipables()) {
                if (equip != nullptr && equip->getName() == name) {
                    item = equip;
                    break;
                }
            }
            if (item == nullptr) {
                for (auto pots : player->currentConsumables()) {
                    if (pots != nullptr && pots->getName() == name) {
                        item = pots;
                        break;
                    }
                }
            }
            if (item == nullptr) {
                setMessageAndNotify("Invalid Command");
                return;
            }
            player->useItem(player, item);
        }
    }
}

void TravelManager::startTravel() { runTravel(); }

void TravelManager::runTravel() {
    while (!map->OnEnemy()) {
        char cmd;
        vector<string> args;
        cin >> cmd;
        switch (cmd) {
            case 'D':
            case 'M': {
                setMessageAndNotify("Input Direction (N,E,S,W)");
                string dir;
                cin >> dir;
                args.emplace_back(dir);
                break;
            }
            case 'P': {
                break;
            }
            case 'L':
            case 'U': {
                setMessageAndNotify("Input Item");
                string name;
                getline(cin, name);
                args.emplace_back(name);
                break;
            }

            case 'T': {
                setMessageAndNotify("Input Location (x,y)");
                string x, y;
                cin >> x >> y;
                args.emplace_back(x);
                args.emplace_back(y);
                break;
            }
        }

        Command fullCmd(cmd, args);

        makeMove(fullCmd);
    }
    setMessageAndNotify("Enemy encountered! Starting battle!");
}

const Map* TravelManager::getMap() const { return map; }