#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "BattleManager.h"
#include "TravelManager.h"

class Command;
class Enemy;
class Player;


class GameManager {
    std::shared_ptr<MapManager> MapManager;
    std::shared_ptr<TravelManager> TravelManager;
    std::shared_ptr<BattleManager> BattleManager;
    std::shared_ptr<Map> Map;
    std::shared_ptr<Player> Player;
    
    public:
    GameManager(std::shared_ptr<MapManager>,std::shared_ptr<TravelManager>,std::shared_ptr<BattleManager>,std::shared_ptr<Map>
    ,std::shared_ptr<Player>);
    void reset();
    void startGame();
    void startTravel();
    void startBattle();
    void endGame();
    std::vector<std::vector<char>> inputMap();
};
#endif
