#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "../HelperClasses/GameConstants.h"

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

class BattleManager;
class TravelManager;
class MsgDisplayManager;
class XWindowManager;
class MapManager;
class Map;
class Player;
class EnemyConf;


class GameManager {
    std::pair<int,int> startCoord;
    std::shared_ptr<MapManager> mapManager;
    std::shared_ptr<TravelManager> travelManager;
    std::shared_ptr<BattleManager> battleManager;
    std::shared_ptr<MsgDisplayManager> msgDisplayerManager;
    std::shared_ptr<XWindowManager> windowManager;
    std::shared_ptr<Map> gameMap;
    std::shared_ptr<Player> player;
    
    int level = 1;

    GameState state;
    public:
    void setStartCoord(std::pair<int,int>);
    GameManager();
    ~GameManager();
    void reset();
    void startGame();
    void startTravel();
    void startBattle();
    void endGame();
    void playGame();
    std::vector<std::vector<char>> inputMap();

    std::map<std::string, EnemyConf> inputEnemyConf();

    GameState getGameState() const;
};
#endif
