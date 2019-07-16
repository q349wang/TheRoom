#include "Tile.h"
#include "Item.h"
#include "Enemy.h"
#include "Tile.h"
#include "ExitTile.h"

#include <memory>
#include <exception>

using namespace std;

/**
 * Signature: ~ExitTile()
 * Purpose: Default destructor
 */
ExitTile::~ExitTile(){}

/**
 * Signature: int getColour()
 * Purpose: Provides the color of the specified tile
 */
int ExitTile::getColour() {
    return TILE_COLOUR;
}