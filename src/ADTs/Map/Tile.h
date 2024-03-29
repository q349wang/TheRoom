#ifndef TILE_H_
#define TILE_H_

#include "../Item/Item.h"
#include "../Entity/Enemy.h"
#include "../../HelperClasses/GameConstants.h"
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
   std::vector<std::shared_ptr<Item>> items_;
   std::vector<std::shared_ptr<Enemy>> enemies_;

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

  void removeEnemy(std::shared_ptr<Enemy>);

  // Provides a const reference to all items on a given tile
  const std::vector<std::shared_ptr<Item>>& getItems() const;

  // Provides a const reference to all enemies on a give tile
  const std::vector<std::shared_ptr<Enemy>>& getEnemies();

  // Provides all items on current tile and clears all items on the tile
  std::vector<std::shared_ptr<Item>> pickupItems();

  // Determines if a specified tile is available to be moved on
  virtual bool available() const;

  // Provides the colour of the current tile
  virtual int getColour() = 0;

  // Clears a tile of all items and enemies
  void clearTile();
};

#endif