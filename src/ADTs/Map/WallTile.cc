#include "WallTile.h"

#include <memory>
#include <exception>

using namespace std;

WallTile::WallTile() {}

/**
 * Signature: ~WallTile()
 * Purpose: Default destructor
 */
WallTile::~WallTile(){}

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
bool WallTile::available() const {
    return false;
}

/**
 * Signature: int getColour()
 * Purpose: Provides the color of the specified tile
 */
int WallTile::getColour() {
    return TILE_COLOUR;
}
