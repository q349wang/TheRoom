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
    BattleManager* BattleManager;
    TravelManager* TravelManager;
    MapManager* MapManager;
    Map* Map;
    
    public:
    GameManager(BattleManager *_battleManager, TravelManager *_travelManager, MapManager *_mapManager, Map *_map);
    void reset();
    void startGame();
    void startTravel();
    void startBattle();
    void endGame();
    std::vector<std::vector<char>> inputMap();
    void notify();
};
#endif
