#include "GameManager.h"

using namespace std;

GameManager::GameManager(): BattleManager{_battleManager}, TravelManager{_travelManager}, MapManager{_mapManager}, Map{_map} {};

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