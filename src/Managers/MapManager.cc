#include "MapManager.h"
#include "EnemyManager.h"
#include "ItemManager.h"

#include "../ADTs/Entity/EnemyConf.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

/**
 * Signature: MapManager(map<string, EnemyConf>)
 * Purpose: Constructs a map manager with specified configurations
 */
MapManager::MapManager(map<string, EnemyConf> configuration)
    : enemy_configuration_{configuration}, item_manager{}, enemy_manager{}
{
    item_manager = make_shared<ItemManager>();
    enemy_manager = make_shared<EnemyManager>(enemy_configuration_);

    // Create seed for psuedorandom number
    srand(time(NULL));
}

/**
 * Signature: ~MapManager()
 * Purpose: Default destructor
 */
MapManager::~MapManager() {}

/**
 * Signature: void populateMap(shared_ptr<Map>, int)
 * Purpose: Populates a map with enemies and items,
 *          all scaled dependent on the current level
 */
void MapManager::populateMap(shared_ptr<Map> empty_map, int level)
{
    empty_map->clearMap();
    cout << "cleared" << endl;

    // Place an appropriate amount items on the map
    for (int i = 0; i < level; i++)
    {
        cout << "starting againnn" << endl;
        // Find an available location
        cout << "row " << empty_map->numRows() << endl;
        int column_index = rand() % empty_map->numRows();
        cout << "col index" << column_index << endl;
        cout <<" col " << empty_map->numColumns(column_index) <<  endl;
        int row_index = rand() % empty_map->numColumns(column_index);
        cout << "row index" << row_index << endl;
        pair<int, int> available_location = empty_map->findNextEmpty(make_pair(row_index, column_index));
        cout << "find next" << available_location.first << " " << available_location.second << endl;
        // Create a scaled item and insert in the specified location
        shared_ptr<Item> new_item = item_manager->createItem(level);
        cout << "Made new item" << endl;
        empty_map->insertItem(new_item, available_location);
        cout << "Trying to insert item" << endl;
    }

    // Place an appropriate amount items on the map
    for (int i = 0; i < level; i++)
    {
        cout << "Making an enemy" << endl;
        // Find an available location
        int column_index = rand() % empty_map->numRows();
        int row_index = rand() % empty_map->numColumns(column_index);
        pair<int, int> available_location = empty_map->findNextEmpty(make_pair(row_index, column_index));

        cout << "Placing Enemy" << endl;
        // Create a scaled enemy and insert in the location
        shared_ptr<Enemy> new_enemy = enemy_manager->createEnemy(level, available_location);
        cout << "Set enemy map" << endl;
        new_enemy->setMap(empty_map);
        cout << "Actually Placing enemy" << endl;
        cout << new_enemy->getName() << endl;
        cout << new_enemy->getColour() << endl;
        cout << new_enemy->getHealth() << endl;
        empty_map->insertEnemy(new_enemy, available_location);
        cout << "Trying to restart" << endl;
    }
}