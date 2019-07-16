#include "ExitTile.h"

#include <memory>
#include <exception>

using namespace std;

ExitTile::ExitTile() {}

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