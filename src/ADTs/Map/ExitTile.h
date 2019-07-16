#ifndef EXITTILE_H_
#define EXITTILE_H_

#include "Item.h"
#include "Enemy.h"
#include "Tile.h"

#include <memory>

/**
 * Class: ExitTile - Derived Class
 * Purpose: ExitTile maintains specific tile information, including but not
 *          limited to the enemies/items currently on the tile
 */
class ExitTile : public Tile {
 private:
 protected:
     // Tile colour to be used for 
    static const int TILE_COLOUR = 1; 

 public:
   // Default constructor
   ExitTile();

   // Default destructor
   ~ExitTile() override;

    // Provides the colour of the current tile
    int getColour() override;
};

#endif;