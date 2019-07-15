#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

/**
 * Class: Map
 * Purpose: Map maintains all tiles, items, and enemies spatial location
 * Note: Map indexing is right and down increasing, hence, the top left 
 *       corner tile will always be considered (0, 0) - with general 
 *       format as (x, y)
 */
class Map {
 private:
  // Structure to maintain coordinate data witihin the map 
   class coord {
      // Maintain position has hashable string and individual coordinates
      std::string position;
      int x_, y_;

      // Coordinate data constructor for pairs of integers
      coord(std::pair<int, int> xy): x_{xy.first}, y_{xy.second}, 
            position{std::to_string(xy.first) + "$" + std::to_string(xy.second)} {}

      // Coordinate data constructor for individual coordinate data
      coord(int x, int y): x_{x}, y_{y}, position{std::to_string(x) + "$" + std::to_string(y)} {}

      // Declare Map as a friend class to allow for use of private member functions
      friend class Map;
   };

  // Maintain the position of the player and the start tile
  coord start_, current_;

  // Current map player
  std::shared_ptr<Player> player_;

  // Maintain the exit tile positions
  std::unordered_map<std::string, std::shared_ptr<Tile>> exits_;

  // Maintains all map tlies and relative locality
  std::vector<std::vector<std::shared_ptr<Tile>>> map_;

  // Maintain a collection of all items on the map
  std::unordered_map<std::string, std::vector<std::shared_ptr<Item>>> items_;

  // Maintain a collection of all enemies on the map
  std::unordered_map<std::string, std::vector<std::shared_ptr<Enemy>>> enemies_;

 protected:
 public:
   
  // Map constructor which requires the current player and
  // the map layout as a two-dimensional vector
  Map(std::shared_ptr<Player> player, std::vector<std::vector<char>> map, 
      std::pair<int, int> start = {0,0},    
      std::unordered_map<std::string, std::vector<std::shared_ptr<Item>>> items = {},
      std::unordered_map<std::string, std::vector<std::shared_ptr<Enemy>>> enemies = {});

  // Map copy constructor
  Map(Map &other);

  // Map move constructor
  Map(Map &&other);

  // Map copy assignment operator
  Map& operator=(Map &other);

  // Map move assignment operator
  Map& operator=(Map &&other);

  // Default destructor to cleanup all allocated data
  ~Map();

  // Insert specified item at specified location
  void insertItem(std::shared_ptr<Item> item, std::pair<int, int> coordinates);

  // Insert specified enemy at specified location
  void insertEnemy(std::shared_ptr<Enemy> enemy, std::pair<int, int> coordinates);

  // Determines the number of columns within map
  int numColumns();

  // Determines the number of rows for a specified column
  // Note: Column is assumed to exist, otherwise will throw exception
  int numRows(int columns);

  // Provides a const reference to a specified tile
  // Note: Coordinates are assumed to exist, otherwise will throw exception
  const Tile& tile(int x, int y);

  // Provides const reference to the current map
  const std::vector<std::vector<std::shared_ptr<Tile>>>& getMap();
};

#endif