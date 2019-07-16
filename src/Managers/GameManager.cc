#include "GameManager.h"
#include "TravelManager.h"

using namespace std;

    GameManager(std::shared_ptr<MapManager> mapManager,std::shared_ptr<TravelManager> travelManager,
    std::shared_ptr<BattleManager> battleManager,std::shared_ptr<Map> map,std::shared_ptr<Player> player):
    MapManager{mapManager}, TravelManager{travelManager}, BattleManager{battleManager}, Map{map}, Player{player};

void GameManager::reset(){
    Player = nullptr;
    TravelManager = nullptr;
    MapManager = nullptr;
    Map = MapManager->setCustomMap(inputMap());
}
void GameManager::startGame(){
    Map = MapManager->setCustomMap(inputMap());
}

void GameManager::startTravel(){
    TravelManager->runTravel();
}

void GameManager::startBattle(){
    BattleManager->runBattle();
}

// isDead or on exit tile.

void GameManager::endGame(){
    
}


std::vector<std::vector<char>> GameManager::inputMap(){
    vector<vector<char>> toReturn;
    int yCoordinate = 0;
    string filename;
    string token;
    cin >> filename;
    string mapInput;
    ifstream input;
    input.open(filename);
    while(input){
        toReturn.resize(yCoordinate+1);
        getline(input,mapInput);
        std::istringstream tokenStream(mapInput);
        while(std::getline(tokenStream,token,' ')){
            toReturn[yCoordinate].emplace_back(token.at(0));
        }
        yCoordinate++;
    }
    return toReturn;
}