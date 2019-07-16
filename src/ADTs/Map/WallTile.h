#ifndef WALLTILE_H_
#define WALLTILE_H_

#include "Tile.h"

#include <memory>

/**
 * Class: WallTile - Derived Class
 * Purpose: WallTile maintains specific tile information, including but not
 *          limited to the enemies/items currently on the tile0
 */
class WallTile : public Tile {
 private:
 protected:
    // Tile colour to be used for 
    static const int TILE_COLOUR = GameColours::Red; 

 public:
   // Default constructor
   WallTile();

   // Default destructor
   ~WallTile() override;

   // Override to inform client that they are inserting an item
   // On an unavailable tile
   void insertItem(std::shared_ptr<Item>) override;
   
   // Override to inform client that they are inserting an enemy
   // On an unavailable tile
   void insertEnemy(std::shared_ptr<Enemy>) override;

   // Determines if a specified tile is available to be moved on
   bool available() const override;

    // Provides the colour of the current tile
    int getColour() override;
};

#endif