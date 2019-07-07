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
	bool exitBattle;
	std::ostringstream msg;
	int eLeft;

public:
	BattleManager(Player *);
	~BattleManager();

	void runEnemyTurn();
	bool runPlayerTurn(const Command &);
	void startBattle(std::vector<Enemy *> *);
	void runBattle();

	bool isBattleEnded() const;
	bool canExitBattle() const;
	std::string getMsg() const;
};
#endif
