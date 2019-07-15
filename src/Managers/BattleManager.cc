#include "BattleManager.h"
#include "../ADTs/Command/Command.h"
#include "../ADTs/Entity/Enemy.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Item/Item.h"

#include <iostream>
#include <sstream>

using namespace std;

BattleManager::BattleManager(shared_ptr<Player>player)
    : player{player}, battleEnded{false}, eList{nullptr}, msg{}, eLeft{0} {}

BattleManager::~BattleManager() {}

void BattleManager::runEnemyTurn() {
    if (eList != nullptr) {
        for (auto enemy : *eList) {
            if (enemy != nullptr) {
                double dmg = enemy->attack(player);
                setMessageAndNotify(enemy->getName() +
                                    " has attacked you for " + to_string(dmg) +
                                    " damage!");
                if (player->isDead()) {
                    battleEnded = true;
                }
                notifyObservers();
            }
        }
    }
}

bool BattleManager::runPlayerTurn(const Command &cmd) {
    vector<string> args = cmd.getArgs();
    bool invalidCmd = false;
    switch (cmd.getCommand()) {
        case 'D': {
            shared_ptr<Item> item = nullptr;
            name = args[1];
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
                invalidCmd = true;
                break;
            }
            setMessageAndNotify(item->getDetails());
            return false;
            break;
        }
        case 'U': {
            if (args.size() != 2) {
                invalidCmd = true;
                break;
            }
            string name = args[0];
            shared_ptr<Entity> target = (name == "me") ? player : nullptr;
            for (auto enemy : *eList) {
                if (enemy != nullptr && enemy->getName() == name) {
                    target = enemy;
                    break;
                }
            }

            shared_ptr<Item> item = nullptr;
            name = args[1];
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
            if (item == nullptr || target == nullptr) {
                invalidCmd = true;
                break;
            }
            player->useItem(target, item);
            setMessageAndNotify("Player used item " + item.getName() + " on " +
                                target->getName() + " .");
            if (target->getHealth() == 0) {
                for (auto enemy : *eList) {
                    if (enemy == target) {
                        enemy == nullptr;
                    }
                }
                eLeft--;
                setMessageAndNotify(target->getName() + " has died.");
                if (eLeft == 0) {
                    battleEnded = true;
                }
            }
            break;
        }

        case 'A': {
            if (args.size() != 1) {
                invalidCmd = true;
                break;
            }
            string name = args[0];
            shared_ptr<Entity> target = nullptr;
            for (auto enemy : *eList) {
                if (enemy != nullptr && enemy->getName() == name) {
                    target = enemy;
                    break;
                }
            }
            if (target == nullptr) {
                invalidCmd = true;
                break;
            }

            double dmg = player->attack(target);
            setMessageAndNotify("Player attacked " + target->getName() +
                                " for " + to_string(dmg));
            if (target->getHealth() == 0) {
                for (auto enemy : *eList) {
                    if (enemy == target) {
                        enemy == nullptr;
                    }
                }
                eLeft--;
                setMessageAndNotify(target->getName() + " has died.");
                if (eLeft == 0) {
                    battleEnded = true;
                }
            }
            break;
        }

        default:
            invalidCmd = true;
            break;
    }

    if (invalidCmd) {
        setMessageAndNotify("Invalid Command");
    } else {
        notifyObservers();
    }
    return !invalidCmd;
}

void BattleManager::startBattle(std::vector<Enemy *> *enemies) {
    battleEnded = false;
    eList = enemies;
    eLeft = (eList != nullptr) ? eList->size() : 0;
    runBattle();
}

void BattleManager::runBattle() {
    while (!battleEnded) {
        bool playerTurn = true;
        do {
            char cmd;
            vector<string> args;
            cin >> cmd;
            switch (cmd) {
                case 'D': {
                    setMessageAndNotify("Input Item");
                    string name;
                    getline(cin, name);
                    args.emplace_back(name);
                    break;
                }
                case 'U': {
                    setMessageAndNotify("Input Item");
                    string name;
                    getline(cin, name);
                    args.emplace_back(name);
                    setMessageAndNotify("Input Target");
                    string target;
                    getline(cin, target);
                    args.emplace_back(target);
                    break;
                }

                case 'A': {
                    setMessageAndNotify("Input Target");
                    string target;
                    getline(cin, target);
                    args.emplace_back(target);
                    break;
                }
            }

            Command fullCmd(cmd, args);

            playerTurn = !runPlayerTurn(fullCmd);
        } while (playerTurn);
        if (battleEnded) {
            break;
        }
        runEnemyTurn();
    }
    setMessageAndNotify("Battle is over.");
}

bool BattleManager::isBattleEnded() const { return battleEnded; }