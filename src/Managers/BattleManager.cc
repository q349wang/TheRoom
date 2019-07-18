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
            items << index << " - " << equip->getName();
        }

        for (auto pots : player->currentConsumables())
        {
            items << index << " - " << pots->getName();
        }

        setMessageAndNotify(items.str());
        return false;
    }
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
        string name = args[0];
        shared_ptr<Entity> target = player;
        if (name != "me")
        {
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
        if (itemIndex < player->currentEquipables().size())
        {
            item = player->currentEquipables()[itemIndex];
            player->equipEquipable(target, item->getName());
        }
        else
        {
            item = player->currentConsumables()[itemIndex - player->currentEquipables().size()];
            player->consumeConsumable(target,
                                      item->getName());
        }
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
            setMessageAndNotify("Input Command (D, U, A)");
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
                string name;
                getline(cin, name);
                args.emplace_back(name);
                break;
            }
            // Use item on target
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