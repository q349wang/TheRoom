#include "Tile.h"
#include "Item.h"
#include "Enemy.h"
#include "Tile.h"
#include "SpaceTile.h"

#include <memory>
#include <exception>

using namespace std;

/**
 * Signature: ~SpaceTile()
 * Purpose: Default destructor
 */
SpaceTile::~SpaceTile(){}

/**
 * Signature: int getColour()
 * Purpose: Provides the color of the specified tile
 */
int SpaceTile::getColour() {
    return TILE_COLOUR;
}

