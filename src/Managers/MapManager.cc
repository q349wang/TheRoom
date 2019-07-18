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
    item_manager = make_unique<ItemManager>();
    enemy_manager = make_unique<EnemyManager>(enemy_configuration_);

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
void MapManager::populateMap(shared_ptr<Map> &empty_map, int level)
{
    empty_map->clearMap();

    // Place an appropriate amount items on the map
    for (int i = 0; i < level; i++)
    {
        // Find an available location
        int column_index = rand() % empty_map->numRows();
        int row_index = rand() % empty_map->numColumns(column_index);
        pair<int, int> available_location = empty_map->findNextEmpty(make_pair(row_index, column_index));
        // Create a scaled item and insert in the specified location
        shared_ptr<Item> new_item = item_manager->createItem(level);
        empty_map->insertItem(new_item, available_location);
    }

    // Place an appropriate amount items on the map
    for (int i = 0; i < level; i++)
    {
        // Find an available location
        int column_index = rand() % empty_map->numRows();
        int row_index = rand() % empty_map->numColumns(column_index);
        pair<int, int> available_location = empty_map->findNextEmpty(make_pair(row_index, column_index));

        // Create a scaled enemy and insert in the location
        try
        {
            shared_ptr<Enemy> new_enemy = enemy_manager->createEnemy(level, available_location);
            new_enemy->setMap(empty_map);
            empty_map->insertEnemy(new_enemy, available_location);
        }
        catch (std::bad_alloc &)
        {
        }
    }
}