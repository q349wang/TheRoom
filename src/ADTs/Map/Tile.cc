#include "Tile.h"
#include "Item.h"
#include "Enemy.h"

#include <memory>
#include <exception>

using namespace std;

/**
 * Signature: void insertItem(shared_ptr<Item>)
 * Purpose: Inserts provided item to tile's collection
 *          of items
 */
void Tile::insertItem(shared_ptr<Item> item) {
    items_.emplace_back(item);
}

/**
 * Signature: void insertEnemy(shared_ptr<Enemy>)
 * Purpose: Inserts provided enemy to tile's collection
 *          of enemies
 */
void Tile::insertEnemy(shared_ptr<Enemy> enemy) {
    enemies_.emplace_back(enemy);
}

/**
 * Signature: const bool available()
 * Purpose: Determines if a specified tile is available
 */
bool Tile::available() const {
    return true;
}
