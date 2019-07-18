#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "BattleManager.h"
#include "TravelManager.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Map/Map.h"

class GameManager {
    pair<int,int> startCoord;
    std::shared_ptr<MapManager> mapManager;
    std::shared_ptr<TravelManager> travelManager;
    std::shared_ptr<BattleManager> battleManager;
    std::shared_ptr<Map> map;
    std::shared_ptr<Player> player;
    
    public:
    void setStartCoord(std::pair<int,int>);
    GameManager();
    void reset();
    void startGame();
    void startTravel();
    void startBattle();
    void endGame();
    void playGame();
    std::vector<std::vector<char>> inputMap();
};
#endif
