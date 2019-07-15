#ifndef BATTLEMANAGER_H_
#define BATTLEMANAGER_H_

#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "../HelperClasses/Subject.h"

class Command;
class Enemy;
class Player;

class BattleManager : public Subject
{
	std::vector<shared_ptr<Enemy>>* eList;
	std::shared_ptr<Player> player;

	bool battleEnded;
	int eLeft;

public:
	BattleManager(std::shared_ptr<Player>);
	~BattleManager();
	// No copying BattleManager
    BattleManager(const BattleManager&) = delete;

	void runEnemyTurn();
	bool runPlayerTurn(const Command &);
	void startBattle(std::vector<std::shared_ptr<Enemy>> *);
	void runBattle();

	bool isBattleEnded() const;
	std::string getMsg() const;
};
#endif
