#include "SpaceTile.h"

#include <memory>
#include <exception>

using namespace std;

SpaceTile::SpaceTile() {}

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
    return getItems().size() == 0 ? TILE_COLOUR : ITEM_TILE_COLOUR;
}

