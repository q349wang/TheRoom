#ifndef SPACETILE_H_
#define SPACETILE_H_

#include "Tile.h"

#include <memory>

/**
 * Class: SpacTile - Derived Class
 * Purpose: SpacTile maintains specific tile information, including but not
 *          limited to the enemies/items currently on the tile
 */
class SpaceTile : public Tile {
 private:
 protected:
    // Tile colour to be used for 
    static const int TILE_COLOUR = GameColours::White; 
    static const int ITEM_TILE_COLOUR = GameColours::Yellow;

 public:
    // Default constructor
    SpaceTile();

    // Default destructor
    ~SpaceTile() override;

    // Provides the colour of the current tile
    int getColour() override;
};

#endif