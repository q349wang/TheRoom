#include "GameManager.h"
#include "TravelManager.h"
#include <memory>

using namespace std;

GameManager::GameManager(){
    player = nullptr;
    travelManager = nullptr;
    mapManager = nullptr;
    battleManager = nullptr;
    map = nullptr;
}

void GameManager::reset(){
    // don't know about this.
    player = nullptr;
    travelManager = nullptr;
    mapManager = nullptr;
    map = MapManager->setCustomMap(inputMap());
}
void GameManager::startGame(){
    mapManager();
    map = MapManager->setCustomMap(inputMap());
    player = make_shared<Player>();
    battleManager{player};
    travelManager{map,player};
}

void GameManager::startTravel(){
    TravelManager->runTravel();
}

void GameManager::startBattle(){
    BattleManager->runBattle();
}

void GameManager::endGame(){
    if(Player->isDead()){
        reset();
    }
}
void GameManager::playGame() {
    Map = MapManager->setCustomMap(inputMap());
    while(true){
        startTravel();
        startBattle();
        if(Player->isDead()){
            reset();
        }
    }
}

vector<vector<char>> GameManager::inputMap(){
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
        istringstream tokenStream(mapInput);
        while(getline(tokenStream,token,' ')){
            toReturn[yCoordinate].emplace_back(token.at(0));
        }
        yCoordinate++;
    }
    return toReturn;
}