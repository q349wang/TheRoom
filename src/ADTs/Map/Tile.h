#ifndef TILE_H_
#define TILE_H_

#include "Item.h"
#include "Enemy.h"

#include <memory>

/**
 * Class: Tile - Abstract Base Class
 * Purpose: Tile maintains specific tile information, including but not
 *          limited to the enemies/items currently on the tile and type of tile
 */
class Tile {
 private:
 protected:
   // Maintain a collection of all items and enemies on a tile
   std::vector<shared_ptr<Item>> items_;
   std::vector<shared_ptr<Enemy>> enemies_;
 public:
   // Default Constructor
   Tile();

   // Define as pure virtual to ensure class is treated as an ABC
   virtual ~Tile() = 0;

   // Inserts specified item into tile's colleciton
   // Defined as virtual in case alternate behaviour is required
   virtual void insertItem(std::shared_ptr<Item>);
   
   // Inserts specified enemy into tile's colleciton
   // Defined as virtual in case alternate behaviour is required
   virtual void insertEnemy(std::shared_ptr<Enemy>);

   // Determines if a specified tile is available to be moved on
   virtual bool available();
};

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

/**
 * Class: WallTile - Derived Class
 * Purpose: WallTile maintains specific tile information, including but not
 *          limited to the enemies/items currently on the tile0
 */
class WallTile : public Tile {
 private:
 protected:
 public:
   // Default constructor
   WallTile();

   // Default destructor
   ~WallTile();

   // Override to inform client that they are inserting an item
   // On an unavailable tile
   void insertItem(std::shared_ptr<Item>) override;
   
   // Override to inform client that they are inserting an enemy
   // On an unavailable tile
   void insertEnemy(std::shared_ptr<Enemy>) override;

   // Determines if a specified tile is available to be moved on
   bool available() override;
};

#endif