#include "GameManager.h"
#include "BattleManager.h"
#include "TravelManager.h"
#include "MapManager.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Map/Map.h"
#include "../ADTs/Entity/EnemyConf.h"
#include <memory>
#include <utility>

using namespace std;

GameManager::GameManager()
    : travelManager{},
      mapManager{},
      battleManager{},
      msgDisplayerManager{},
      windowManager{},
      gameMap{},
      player{},
      state{GameState::None}
{
}

void GameManager::setStartCoord(pair<int, int> input)
{
    startCoord = input;
}
void GameManager::reset()
{
    mapManager->populateMap(gameMap, level);
}
void GameManager::startGame()
{
    unordered_map<string, vector<shared_ptr<Item>>> items;
    unordered_map<string, vector<shared_ptr<Enemy>>> enemies;
    gameMap = make_shared<Map>(player, inputMap(), startCoord, items, enemies);
    player = make_shared<Player>();
    mapManager->populateMap(gameMap, level);
    player->setMap(gameMap);
    battleManager = make_shared<BattleManager>(player);
    travelManager = make_shared<TravelManager>(gameMap, player);
    msgDisplayerManager = make_shared<MsgDisplayerManager>(cin);
    windowManager = make_shared<XWindowManager>(this, gameMap);
    playGame();
}

void GameManager::startTravel()
{
    state = GameState::Travel;
    travelManager->startTravel();
}

void GameManager::startBattle()
{
    state == GameState::Battle;
    battleManager->startBattle();
}

void GameManager::endGame()
{
    if (player->isDead())
    {
        reset();
    }
}
void GameManager::playGame()
{
    gameMap = mapManager->setCustomMap(inputMap());
    while (true)
    {
        startTravel();
        if (travelManager->isExiting())
        {
            level++;
            reset();
        }
        else
        {
            startBattle();
            if (player->isDead())
            {
                cout << "Final Score: " << level << endl;
                break;
            }
        }
    }
}

vector<vector<char>> GameManager::inputMap()
{
    // file format: two ints to represent the starting co-ordinates followed by space seperated components of the map itself.
    vector<vector<char>> toReturn;
    int yCoordinate = 0;
    string filename;
    string token;
    cout << "Input a file for input map" << endl;
    cin >> filename;
    string mapInput;
    ifstream input;
    int y;
    int x;
    input.open(filename);
    while (!input)
    {
        cout << "Error opening file. Try again" << endl;
        cin >> filename;
        input.open(filename);
    }
    input >> y >> x;
    setStartCoord(make_pair(y, x));
    while (input)
    {
        toReturn.resize(yCoordinate + 1);
        getline(input, mapInput);
        istringstream tokenStream(mapInput);
        while (getline(tokenStream, token, ' '))
        {
            toReturn[yCoordinate].emplace_back(token.at(0));
        }
        yCoordinate++;
    }
    input.close();
    return toReturn;
}

map<string, EnemyConf> GameManager::inputEnemyConf()
{
    map<string, EnemyConf> confMap;
    string filename;
    string token;
    cout << "Input a file for input map" << endl;
    cin >> filename;
    string mapInput;
    ifstream input;
    int y;
    int x;
    input.open(filename);
    while (!input)
    {
        cout << "Error opening file. Try again" << endl;
        cin >> filename;
        input.open(filename);
    }
    // Assumes that enemy config file is properly formatted
    while (input)
    {
        // Build enemy stats;
        string name;
        input >> name;
        int weight;
        input >> weight;

        // Base and scale of health
        pair<double, double> health;
        input >> health.first >> health.second;

        // Base and scale of energy
        pair<double, double> energy;
        input >> energy.first >> energy.second;

        // Base and scale of armour
        pair<double, double> armour;
        input >> armour.first >> armour.second;

        // Base and scale of attack
        pair<double, double> attack;
        input >> attack.first >> attack.second;

        EnemyConf conf{weight, health, energy, armour, attack};
        confMap[name] = conf;
    }
    input.close();

    return confMap;
}