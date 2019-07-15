#ifndef SPACETILE_H_
#define SPACETILE_H_

#include "Item.h"
#include "Enemy.h"
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
 public:
   // Default constructor
   SpaceTile();

   // Default destructor
   ~SpaceTile();
};

#endif