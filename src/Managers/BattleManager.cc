#include "BattleManager.h"
#include "../ADTs/Command/Command.h"
#include "../ADTs/Entity/Enemy.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Item/Item.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

BattleManager::BattleManager(shared_ptr<Player> player)
    : eList{nullptr}, player{player}, battleEnded{false}, eLeft{0} {}

BattleManager::~BattleManager() {}

void BattleManager::runEnemyTurn()
{
    if (eList != nullptr)
    {
        for (auto enemy : *eList)
        {
            if (enemy != nullptr)
            {
                double dmg = enemy->attack(player);
                setMessageAndNotify(enemy->getName() +
                                    " has attacked you for " + to_string(dmg) +
                                    " damage!");
                if (player->isDead())
                {
                    battleEnded = true;
                }
                notifyObservers();
            }
        }
    }
}

bool BattleManager::runPlayerTurn(const Command &cmd)
{
    vector<string> args = cmd.getArgs();
    bool invalidCmd = false;
    switch (cmd.getCommand())
    {
    case 'D':
    {
        shared_ptr<Item> item = nullptr;
        string name = args[1];
        for (auto equip : player->currentEquipables())
        {
            if (equip != nullptr && equip->getName() == name)
            {
                item = equip;
                break;
            }
        }
        if (item == nullptr)
        {
            for (auto pots : player->currentConsumables())
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
            invalidCmd = true;
            break;
        }
        setMessageAndNotify(item->getName());
        return false;
        break;
    }
    case 'U':
    {
        if (args.size() != 2)
        {
            invalidCmd = true;
            break;
        }
        string name = args[0];
        shared_ptr<Entity> target = player;
        if (name != "me")
        {
            int tarIndex = 0;
            try
            {
                tarIndex = stoi(args[0]);
            }
            catch (const invalid_argument &e)
            {
                setMessageAndNotify("Invalid Target");
                return false;
            }
            if (tarIndex >= 0 && tarIndex < eList->size())
            {
                target = eList->at(tarIndex);
            }
            else
            {
                setMessageAndNotify("Invalid Target");
                return false;
            }
        }

        shared_ptr<Item> item = nullptr;
        name = args[1];
        for (auto equip : player->currentEquipables())
        {
            if (equip != nullptr && equip->getName() == name)
            {
                item = equip;
                break;
            }
        }
        if (item == nullptr)
        {
            for (auto pots : player->currentConsumables())
            {
                if (pots != nullptr && pots->getName() == name)
                {
                    item = pots;
                    break;
                }
            }
        }
        if (item == nullptr || target == nullptr)
        {
            invalidCmd = true;
            break;
        }
        // TODO
        //player->useItem(target, item);
        setMessageAndNotify("Player used item " + item->getName() + " on " +
                            target->getName() + " .");
        if (target->getHealth() == 0)
        {
            for (auto enemy : *eList)
            {
                if (enemy == target)
                {
                    enemy == nullptr;
                }
            }
            eLeft--;
            setMessageAndNotify(target->getName() + " has died.");
            if (eLeft == 0)
            {
                battleEnded = true;
            }
        }
        break;
    }

    case 'A':
    {
        if (args.size() != 1)
        {
            invalidCmd = true;
            break;
        }
        shared_ptr<Enemy> target = nullptr;
        int tarIndex = 0;
        try
        {
            tarIndex = stoi(args[0]);
        }
        catch (const invalid_argument &e)
        {
            setMessageAndNotify("Invalid Target");
            return false;
        }
        if (tarIndex >= 0 && tarIndex < eList->size())
        {
            target = eList->at(tarIndex);
        }
        else
        {
            setMessageAndNotify("Invalid Target");
            return false;
        }
        if (target == nullptr)
        {
            invalidCmd = true;
            break;
        }

        double dmg = player->attack(target);
        setMessageAndNotify("Player attacked " + target->getName() +
                            " for " + to_string(dmg));
        if (target->getHealth() == 0)
        {
            for (auto enemy : *eList)
            {
                if (enemy == target)
                {
                    enemy == nullptr;
                }
            }
            eLeft--;
            setMessageAndNotify(target->getName() + " has died.");
            if (eLeft == 0)
            {
                battleEnded = true;
            }
        }
        break;
    }

    default:
        invalidCmd = true;
        break;
    }

    if (invalidCmd)
    {
        setMessageAndNotify("Invalid Command");
    }
    else
    {
        notifyObservers();
    }
    return !invalidCmd;
}

void BattleManager::startBattle(vector<shared_ptr<Enemy>> *enemies)
{
    battleEnded = false;
    eList = enemies;
    eLeft = (eList != nullptr) ? eList->size() : 0;
    runBattle();
}

void BattleManager::runBattle()
{
    while (!battleEnded)
    {
        bool playerTurn = true;
        do
        {
            char cmd;
            vector<string> args;
            cin >> cmd;
            switch (cmd)
            {
            case 'D':
            {
                setMessageAndNotify("Input Item");
                string name;
                getline(cin, name);
                args.emplace_back(name);
                break;
            }
            case 'U':
            {
                setMessageAndNotify("Input Item");
                string name;
                getline(cin, name);
                args.emplace_back(name);
                setMessageAndNotify("Input Target (\"me\" for self)");
                string target;
                cin >> target;
                args.emplace_back(target);
                break;
            }

            case 'A':
            {
                setMessageAndNotify("Input Target");
                string target;
                cin >> target;
                args.emplace_back(target);
                break;
            }
            }

            Command fullCmd(cmd, args);

            playerTurn = !runPlayerTurn(fullCmd);
        } while (playerTurn);
        if (battleEnded)
        {
            break;
        }
        runEnemyTurn();
    }
    setMessageAndNotify("Battle is over.");
}

bool BattleManager::isBattleEnded() const { return battleEnded; }