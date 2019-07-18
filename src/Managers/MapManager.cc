#include "MapManager.h"

using namespace std;

/**
 * Signature: void populateMap(shared_ptr<Map>, int)
 * Purpose: Populates a map with enemies and items,
 *          all scaled dependent on the current level
 */
void MapManager::populateMap(shared_ptr<Map> empty_map, int level) {
    int space_tiles = empty_map->getNumSpaces() - 1;
}