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
 * Signature: void insertItem(shared_ptr<Item>)
 * Purpose: Informs client that they are inserting an item
 *          on an unavailable tile
 */
void WallTile::insertItem(shared_ptr<Item> item) {
    throw domain_error{"Cannot insert item onto a wall tile!"};
}

/**
 * Signature: void insertEnemy(shared_ptr<Enemy>)
 * Purpose: Informs client that they are inserting an enemy
 *          on an unavailable tile
 */
void WallTile::insertEnemy(shared_ptr<Enemy> enemy) {
    throw domain_error{"Cannot insert enemy onto a wall tile!"};
}

/**
 * Signature: const bool available()
 * Purpose: Determines if a specified tile is available
 */
bool Tile::available() const {
    return true;
}

/**
 * Signature: const bool available()
 * Purpose: Determines if a specified tile is available
 */
bool WallTile::available() const {
    return false;
}
