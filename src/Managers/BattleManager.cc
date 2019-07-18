#include "BattleManager.h"
#include "../ADTs/Command/Command.h"
#include "../ADTs/Entity/Enemy.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Item/Item.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

BattleManager::BattleManager(shared_ptr<Player> player)
    : eList{}, player{player}, battleEnded{false}, eLeft{0} {}

BattleManager::~BattleManager() {}

void BattleManager::runEnemyTurn()
{
    for (auto enemy : eList)
    {
        if (enemy->getHealth() > 0)
        {
            double dmg = enemy->attack(player);
            string info = enemy->getName() +
                          " has attacked you for " + to_string(dmg) +
                          " damage!";
            setMessageAndNotify(info);
            if (player->isDead())
            {
                battleEnded = true;
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
    case 'L':
    {
        ostringstream items;
        int index = 0;
        for (auto equip : player->currentEquipables())
        {
            items << index << " - " << equip->getName() << endl;
            index++;
        }

        for (auto pots : player->currentConsumables())
        {
            items << index << " - " << pots->getName() << endl;
            index++;
        }

        setMessageAndNotify(items.str());
        return false;
    }
    case 'D':
    {
        unsigned int itemIndex = 0;
        try
        {
            itemIndex = stoi(args[0]);
        }
        catch (const invalid_argument &e)
        {
            setMessageAndNotify("Invalid Item");
            return false;
        }
        if (itemIndex >= player->currentEquipables().size() + player->currentConsumables().size())
        {
            setMessageAndNotify("Invalid Item");
            return false;
        }
        shared_ptr<Item> item;
        if (itemIndex < player->currentEquipables().size())
        {
            item = player->currentEquipables()[itemIndex];
        }
        else
        {
            item = player->currentConsumables()[itemIndex - player->currentEquipables().size()];
        }
        ostringstream itemDesc;
        itemDesc << fixed << setprecision(2);
        itemDesc << item->getName() << endl;
        map<string, StatMod> desc = item->getModifiers();
        for (auto it = desc.begin(); it != desc.end(); ++it)
        {
            itemDesc << it->first << ": Adder: "
                     << it->second.getAdder() << " Multiplier: "
                     << it->second.getMultiplier() << endl;
        }
        if (item->getType() == 1)
        {
            itemDesc << "Passive:" << endl;
            map<string, StatMod> pass = static_pointer_cast<Equipable>(item)->getPassive();
            for (auto it = pass.begin(); it != pass.end(); ++it)
            {
                itemDesc << it->first << ": Adder: "
                         << it->second.getAdder() << " Multiplier: "
                         << it->second.getMultiplier() << endl;
            }
        }

        setMessageAndNotify(itemDesc.str());
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
        string name = args[1];
        shared_ptr<Entity> target = player;
        if (name != "me")
        {
            unsigned int tarIndex = 0;
            try
            {
                tarIndex = stoi(args[1]);
            }
            catch (const invalid_argument &e)
            {
                setMessageAndNotify("Invalid Target 1");
                return false;
            }
            if (tarIndex >= 0 && tarIndex < eList.size())
            {
                target = eList.at(tarIndex);
            }
            else
            {
                setMessageAndNotify("Invalid Target: " + to_string(tarIndex));
                return false;
            }
        }
        if (target == nullptr)
        {
            invalidCmd = true;
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
            return false;
        }
        if (itemIndex >= player->currentEquipables().size() + player->currentConsumables().size())
        {
            setMessageAndNotify("Invalid Item");
            return false;
        }
        shared_ptr<Item> item;
        bool success = false;
        if (itemIndex < player->currentEquipables().size())
        {
            item = player->currentEquipables()[itemIndex];
            success = player->equipEquipable(target, itemIndex);
        }
        else
        {
            item = player->currentConsumables()[itemIndex - player->currentEquipables().size()];
            success = player->consumeConsumable(target,
                                                itemIndex - player->currentEquipables().size());
        }
        if (success)
        {
            string info = "Player used item " + item->getName() + " on " +
                          target->getName() + " .";
            setMessageAndNotify(info);
            if (target->getHealth() <= 0)
            {
                for (auto enemy : eList)
                {
                    if (enemy == target)
                    {
                        enemy == nullptr;
                    }
                }
                eLeft--;
                target->dropAllItems();
                setMessageAndNotify(target->getName() + " has died.");
                if (eLeft == 0)
                {
                    battleEnded = true;
                }
            }
        }
        else
        {
            setMessageAndNotify("Could not use item on target");
            return false;
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
        unsigned int tarIndex = 0;
        try
        {
            tarIndex = stoi(args[0]);
        }
        catch (const invalid_argument &e)
        {
            setMessageAndNotify("Invalid Target");
            return false;
        }
        if (tarIndex >= 0 && tarIndex < eList.size())
        {
            target = eList.at(tarIndex);
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
        string info = "Player attacked " + target->getName() +
                      " for " + to_string(dmg);
        setMessageAndNotify(info);
        if (target->getHealth() <= 0)
        {
            for (auto enemy : eList)
            {
                if (enemy == target)
                {
                    enemy == nullptr;
                }
            }
            eLeft--;
            target->dropAllItems();
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
    return !invalidCmd;
}

void BattleManager::startBattle(const vector<shared_ptr<Enemy>> &enemies)
{
    battleEnded = false;
    eList = enemies;
    eLeft = eList.size();
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
            setMessageAndNotify("Input Command (D, U, A, L)");
            cin >> cmd;
            switch (cmd)
            {
                //List all items
            case 'L':
            {
                break;
            }
            // Get details of item
            case 'D':
            {
                setMessageAndNotify("Input Item");
                string index;
                cin >> index;
                args.emplace_back(index);
                break;
            }
            // Use item on target
            case 'U':
            {
                setMessageAndNotify("Input Item");
                string index;
                cin >> index;
                args.emplace_back(index);
                setMessageAndNotify("Input Target (\"me\" for self)");
                string target;
                cin >> target;
                args.emplace_back(target);
                break;
            }
            // Attack target
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