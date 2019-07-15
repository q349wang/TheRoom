#ifndef BATTLEMANAGER_H_
#define BATTLEMANAGER_H_

#include <vector>
#include <string>

#include "../HelperClasses/Subject.h"

class Command;
class Enemy;
class Player;

class BattleManager : public Subject {
    std::vector<Enemy*>* eList;
    Player* player;

    bool battleEnded;
    std::string msg;
    int eLeft;
    public:
    BattleManager(Player *);
    ~BattleManager();

    void runEnemyTurn();
    bool runPlayerTurn(const Command&);
    void startBattle(std::vector<Enemy*>*);
    void runBattle();
    void endBattle();

    bool isBattleEnded();
    std::string getMsg();
};
#endif
