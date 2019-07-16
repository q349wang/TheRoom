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

/**
 * Signature: const vector<shared_ptr<Item>>& getItems()
 * Purpose: Provides a const reference to the items on the current tile
 */
const vector<shared_ptr<Item>>& Tile::getItems() {
    return items_;
}

/**
 * Signature: const vector<shared_ptr<Enemy>>& getEnemies()
 * Purpose: Provides a const reference to the enemies on the current tile
 */
const vector<shared_ptr<Enemy>>& Tile::getEnemies() {
    return enemies_;
}

/**
 * Signature: vector<shared_ptr<Item>> pickupItems();
 * Purpose: Provides all items on the current tile, and empties tile
 */
vector<shared_ptr<Item>> Tile::pickupItems() {
    vector<shared_ptr<Item>> items{items_};
    items_.clear();
    return items;
}
