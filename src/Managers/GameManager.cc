#include "GameManager.h"
#include "BattleManager.h"
#include "TravelManager.h"
#include "MapManager.h"
#include "MsgDisplayManager.h"
#include "XWindowManager.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Entity/Warrior.h"
#include "../ADTs/Entity/Mage.h"
#include "../ADTs/Entity/Ranger.h"
#include "../ADTs/Map/Map.h"
#include "../ADTs/Map/Tile.h"
#include "../ADTs/Entity/EnemyConf.h"
#include <memory>
#include <utility>

using namespace std;

GameManager::GameManager()
    : startCoord{0, 0},
      mapManager{},
      travelManager{},
      battleManager{},
      msgDisplayerManager{},
      windowManager{},
      gameMap{},
      player{},
      state{GameState::NoState}
{
}

GameManager::~GameManager()
{
    battleManager->detach(windowManager.get());
    battleManager->detach(msgDisplayerManager.get());

    travelManager->detach(windowManager.get());
    travelManager->detach(msgDisplayerManager.get());
}

void GameManager::setStartCoord(pair<int, int> input)
{
    startCoord = input;
}
void GameManager::reset()
{
    player->forcePosition(startCoord);
    mapManager->populateMap(gameMap, level);
}
void GameManager::startGame()
{
    unordered_map<string, vector<shared_ptr<Item>>> items;
    unordered_map<string, vector<shared_ptr<Enemy>>> enemies;

    cout << "Choose hero: Warrior = 0, Mage = 1, Ranger = 2" << endl;
    int hero = 0;
    cin >> hero;
    switch (hero)
    {
    case 1:
        player = make_shared<Mage>(150, 300, 30, 10, make_pair(1, 1));
        break;
    case 2:
        player = make_shared<Ranger>(200, 200, 20, 15, make_pair(1, 1));
        break;
    case 0:
        player = make_shared<Warrior>(300, 200, 15, 20, make_pair(1, 1));
        break;
    default:
        cout << "Invalid hero. Exiting..." << endl;
        return;
    }
    vector<vector<char>> current_map = inputMap();


    for(auto it = current_map.begin(); it != current_map.end(); ++it) {
        cout << "hello" << endl;
        for(auto bi = (*it).begin(); bi != (*it).end(); ++bi) {
            cout << (*bi) << " ";
        }
        cout << endl;
    }

    gameMap = make_shared<Map>(player, current_map, make_pair(1, 1), items, enemies);


    battleManager = make_shared<BattleManager>(player);
    travelManager = make_shared<TravelManager>(gameMap, player);
    mapManager = make_shared<MapManager>(inputEnemyConf());
    mapManager->populateMap(gameMap, level);
    player->setMap(gameMap);
    msgDisplayerManager = make_shared<MsgDisplayManager>(cout);
    windowManager = make_shared<XWindowManager>(this, gameMap);

    battleManager->attach(windowManager.get());
    battleManager->attach(msgDisplayerManager.get());

    travelManager->attach(windowManager.get());
    travelManager->attach(msgDisplayerManager.get());
    playGame();
}

void GameManager::startTravel()
{
    state = GameState::Travel;
    travelManager->startTravel();
}

void GameManager::startBattle()
{
    state = GameState::Battle;
    battleManager->startBattle(gameMap->tile(player->getPosition()).getEnemies());
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
	 	cout << "You Died!" << endl;
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
    getline(input,mapInput);
    while (input)
    {
        getline(input, mapInput);
        if(mapInput.size()!=0){
            toReturn.resize(yCoordinate + 1);
            istringstream tokenStream(mapInput);
            while (getline(tokenStream, token, ' '))
            {
                toReturn[yCoordinate].emplace_back(token.at(0));
            }
            yCoordinate++;
        }
    }
    input.close();
    return toReturn;
}

map<string, EnemyConf> GameManager::inputEnemyConf()
{
    map<string, EnemyConf> confMap;
    string filename;
    cout << "Input a file for enemy config" << endl;
    cin >> filename;
    ifstream input;
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

GameState GameManager::getGameState() const
{
    return state;
}
