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
 public:
   // Default constructor
   ExitTile();

   // Default destructor
   ~ExitTile();
};

#endif;