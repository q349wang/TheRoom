#include "BattleManager.h"
#include "../ADTs/Command/Command.h"
#include "../ADTs/Entity/Enemy.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Item/Item.h"

#include <sstream>
#include <iostream>

using namespace std;

BattleManager::BattleManager(Player *player) : player{player},
																							 battleEnded{false},
																							 exitBattle{false},
																							 eList{nullptr},
																							 msg{},
																							 eLeft{0} {}

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
				msg.clear();
				msg << enemy->getName() << " has attacked you for " << dmg << " damage!";
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
	case 'U':
	{
		if (args.size() != 2)
		{
			invalidCmd = true;
			break;
		}
		string name = args[0];
		Entity *target = (name == "me") ? player : nullptr;
		for (auto enemy : *eList)
		{
			if (enemy != nullptr && enemy->getName() == name)
			{
				target = enemy;
				break;
			}
		}

		Item *item = nullptr;
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
		player->useItem(target, item);
		msg.clear();
		msg << "Player used item " << item.getName() << " on " << target->getName() << " .";
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
			msg << " " << target->getName() << " has died.";
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
		string name = args[0];
		Enemy *target = nullptr;
		for (auto enemy : *eList)
		{
			if (enemy != nullptr && enemy->getName() == name)
			{
				target = enemy;
				break;
			}
		}
		if (target == nullptr)
		{
			invalidCmd = true;
			break;
		}

		double dmg = player->attack(target);
		msg.clear();
		msg << "Player attacked " << target->getName() << " for " << dmg << " damage.";
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
			msg << " " << target->getName() << " has died.";
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
		msg.clear();
		msg << "Invalid command";
	}
	notifyObservers();
	return !invalidCmd;
}

void BattleManager::startBattle(std::vector<Enemy *> *enemies)
{
	battleEnded = false;
	exitBattle = false;
	eList = enemies;
	eLeft = (eList != nullptr) ? eList->size() : 0;
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
			msg.clear();
			switch (cmd)
			{
			case 'U':
			{
				msg << "Input Item";
				notifyObservers();
				string name;
				getline(cin, name);
				args.emplace_back(name);
				msg << "Input Target";
				notifyObservers();
				string target;
				getline(cin, target);
				args.emplace_back(target);
				break;
			}

			case 'A':
			{
				msg << "Input Target";
				notifyObservers();
				string target;
				getline(cin, target);
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
	exitBattle = true;
	notifyObservers();
}

string BattleManager::getMsg()
{
	return msg.str();
}

bool BattleManager::isBattleEnded() { return battleEnded; }

bool BattleManager::canExitBattle() { return exitBattle; }