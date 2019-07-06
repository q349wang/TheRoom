#include "BattleManager.h"
#include "../ADTs/Command/Command.h"
#include "../ADTs/Entity/Enemy.h"
#include "../ADTs/Entity/Player.h"

using namespace std;

BattleManager::BattleManager(Player *player) : player{player}, battleEnded{false},
                                               eList{nullptr}, msg{}, eLeft{0} {}

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
                msg = enemy->getName() + " has attacked you for " + dmg + " damage!";
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
    vector<char> args = cmd.getArgs();
    switch (cmd.getCommand())
    {
    case 'U':
    {
        if (args.size() != 2)
        {
            msg = "Invalid command";
            return false;
        }
        string name = args[0];
        Enemy *target = nullptr;
        for (auto enemy : *eList)
        {
            if (enemy != nullptr && enemy->getName() = name)
            {
                target = enemy;
                break;
            }
        }

        Item *item = nullptr;
        for (auto equip : player->)
        {
            if (equip != nullptr && equip->getName() = name)
            {
                item = equip;
                break;
            }
        }
        if (item )
        player->useItem();
        break;
    }

    case 'A':
    {
        if (args.size() != 1)
        {
            msg = "Invalid command";
            return false;
        }
        break;
    }

    default:
        msg = "Invalid command";
        return false;
        break;
    }
}

void BattleManager::startBattle(std::vector<Enemy *> *enemies)
{
    eList = enemies;
    eLeft = (eList != nullptr) ? eList->size() : 0;
}

void BattleManager::runBattle()
{
    while (!battleEnded)
    {
    }
}