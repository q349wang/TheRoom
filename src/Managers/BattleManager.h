#ifndef BATTLEMANAGER_H_
#define BATTLEMANAGER_H_

#include <vector>
#include <string>
#include <sstream>

#include "../HelperClasses/Subject.h"

class Command;
class Enemy;
class Player;

class BattleManager : public Subject
{
	std::vector<Enemy *> *eList;
	Player *player;

	bool battleEnded;
	int eLeft;

public:
	BattleManager(Player *);
	~BattleManager();
	// No copying BattleManager
    BattleManager(const BattleManager&) = delete;

	void runEnemyTurn();
	bool runPlayerTurn(const Command &);
	void startBattle(std::vector<Enemy *> *);
	void runBattle();

	bool isBattleEnded() const;
	std::string getMsg() const;
};
#endif
