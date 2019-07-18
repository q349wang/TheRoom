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

void GameManager::setStartCoord(pair<int,int>input){
    startCoord = input;
}
void GameManager::reset(){
    // don't know about this.
    player = nullptr;
    travelManager = nullptr;
    mapManager = nullptr;
    map = MapManager->setCustomMap(inputMap());
}
void GameManager::startGame(){
    unordered_map<string, vector<shared_ptr<Item>>> items;
    unordered_map<string, vector<shared_ptr<Enemy>>> enemies;
    map = make_shared<Map> (player,inputMap(),startCoord,items,enemies);
    player = make_shared<Player>();
    mapManager->populateMap(map,0);
    player->setMap(map);
    battleManager{player};
    travelManager{map,player};
}

void GameManager::startTravel(){
    travelManager->runTravel();
}

void GameManager::startBattle(){
    battleManager->runBattle();
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
    int y;
    int x;
    input.open(filename);
    cin >> y >> x;
    setStartCoord(make_pair(y,x));
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