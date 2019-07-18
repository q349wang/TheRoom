#include "Map.h"
#include "Tile.h"
#include "ExitTile.h"
#include "SpaceTile.h"
#include "WallTile.h"

#include "../Entity/Enemy.h"
#include "../Entity/Player.h"
#include "../Item/Item.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

/**
     * Signature: Map(shared_ptr<Player>, vector<vector<char>>, pair<int, int>, unordered_map<string, 
     *                shared_ptr<Item>>, unordered_map<string, shared_ptr<Enemy>>)
     * Purpose: Constructs map with a specified player, map layout, start tile, and any pre-existing enemies/items
     * Note: Additionally pads the map construction with a layer of walls
     */
Map::Map(shared_ptr<Player> player, vector<vector<char>> map,
         pair<int, int> start,
         unordered_map<string, vector<shared_ptr<Item>>> items,
         vector<shared_ptr<Enemy>> enemies) : start_{start}, current_{start}, player_{player},
                                              items_{items}, enemies_{enemies}
{

    vector<shared_ptr<Tile>> column = {}, first = {}, last = {};
    num_space_ = num_wall_ = num_exit_ = 0;

    for (size_t f = 0; f < (map[0].size() + 2); f++)
    {
        first.emplace_back(make_shared<WallTile>(WallTile{}));
        num_wall_++;
    }

    for (size_t l = 0; l < (map[map.size() - 1].size() + 2); l++)
    {
        last.emplace_back(make_shared<WallTile>(WallTile{}));
        num_wall_++;
    }

    map_.emplace_back(first);

    // Iterate through the provided map specifications to construct map tiles
    for (auto row = map.begin(); row != map.end(); ++row)
    {
        column.emplace_back(make_shared<WallTile>(WallTile{}));
        num_wall_++;
        for (auto col = row->begin(); col != row->end(); ++col)
        {
            // If the tile is marked as 'E' it is assumed to be an exit tile
            if (*col == 'E')
            {
                column.emplace_back(make_shared<ExitTile>(ExitTile{}));
                coord coordPos = coord(distance(map.begin(), row), distance(row->begin(), col));
                exits_.emplace(coordPos.position, column.back());
                num_exit_++;
            }
            // If the tile is marked as 'W' it is assumed to be an wall tile
            else if (*col == 'W')
            {
                column.emplace_back(make_shared<WallTile>(WallTile{}));
                num_wall_++;
            }
            // Any other input is assumed to be a basic space tile
            else
            {
                column.emplace_back(make_shared<SpaceTile>(SpaceTile{}));
                num_space_++;
            }
        }
        column.emplace_back(make_shared<WallTile>(WallTile{}));
        map_.emplace_back(column);
        column.clear();
        num_wall_++;
    }

    map_.emplace_back(last);
}

/**
 * Signature: ~Map()
 * Purpose: Default destructor
 */
Map::~Map() {}

/**
    * Signature: void insertItem(shared_ptr<Item>, pair<int, int>) : void
    * Purpose: Inserts provided item at specified location on the map
    */
void Map::insertItem(shared_ptr<Item> item, pair<int, int> coordinates)
{
    coord location = coord{coordinates};
    ((map_.at(location.y_)).at(location.x_))->insertItem(item);

    if (items_.find(location.position) == items_.end())
    {
        items_.emplace(location.position, vector<shared_ptr<Item>>{item});
    }
    else
    {
        items_[location.position].emplace_back(item);
    }
}

/**
     * Signature: void Map(shared_ptr<Player>, vector<vector<char>>, pair<int, int>, unordered_map<string, 
     *                shared_ptr<Item>>, unordered_map<string, shared_ptr<Enemy>>)
     * Purpose: Constructs map with a specified player, map layout, start tile, and any pre-existing enemies/items
     */
void Map::insertEnemy(shared_ptr<Enemy> enemy, pair<int, int> coordinates)
{
    coord location = coord{coordinates};
    ((map_.at(location.y_)).at(location.x_))->insertEnemy(enemy);

    enemies_.emplace_back(enemy);
}

/**
     * Signature: int numRows()
     * Purpose: Provides the number of rows within the map
     */
int Map::numRows()
{
    return map_.size();
}

/**
     * Signature: int numColumns(int)
     * Purpose: Provides the number of columns at a specified row 
     */
int Map::numColumns(int row)
{
    return (map_.at(row)).size();
}

/**
     * Signature: const Tile& tile(int, int)
     * Purpose: Provides a const reference to a specified tile
     */
Tile &Map::tile(int x, int y) const
{
    return *((map_.at(y)).at(x));
}
/**
     * Signature: const Tile& tile(pair<int, int>)
     * Purpose: Provides a const reference to a specified tile
     */
Tile &Map::tile(const pair<int, int> &coord) const
{
    return *((map_.at(coord.second)).at(coord.first));
}

/**
     * Signature: const vector<vector<shared_ptr<Tile>>>& getMap()
     * Purpose: Provides a const reference to the current map
     */
const vector<vector<shared_ptr<Tile>>> &Map::getMap() const
{
    return map_;
}

/**
     * Signature: const shared_ptr<Player> &getPlayer()
     * Purpose: Provides a const reference to the current player
     */
const shared_ptr<Player> &Map::getPlayer() const
{
    return player_;
}

/**
     * Signature: void moveEnemies()
     * Purpose: Moves all enemies currently on the map towards the player
     */
void Map::moveEnemies()
{
    //unordered_map<string, vector<shared_ptr<Enemy>>> currentEnemies = enemies_;
    for (shared_ptr<Enemy> enem : enemies_)
    {
        // Skip dead enemies
        if (enem->isDead())
        {
            continue;
        }

        coord position = coord{enem->getPosition()};
        coord currentPlayer = coord{player_->getPosition()};
        vector<char> movement;

        int x_difference = currentPlayer.x_ - position.x_; // Positive, player right of enemy
        int y_difference = currentPlayer.y_ - position.y_; // Positive, player lower than enemy
        if (x_difference == 0 && y_difference == 0) continue;
        if (abs(x_difference) >= abs(y_difference))
        {
            if (x_difference >= 0)
            {
                if (y_difference >= 0)
                {
                    movement = {'E', 'S'};
                }
                else
                {
                    movement = {'E', 'N'};
                }
            }
            else
            {
                if (y_difference >= 0)
                {
                    movement = {'W', 'S'};
                }
                else
                {
                    movement = {'W', 'N'};
                }
            }
        }
        else
        {
            if (x_difference >= 0)
            {
                if (y_difference >= 0)
                {
                    movement = {'S', 'E'};
                }
                else
                {
                    movement = {'N', 'E'};
                }
            }
            else
            {
                if (y_difference >= 0)
                {
                    movement = {'S', 'W'};
                }
                else
                {
                    movement = {'N', 'W'};
                }
            }
        }

        // Iterate through all enemies on the current tile, and all possible directions
        // In order of increasing distance, and make the move towards the closest location
        for (auto direction = movement.begin(); direction != movement.end(); ++direction)
        {
            pair<int, int> oldPos = enem->getPosition();
            coord oldCoord{oldPos};

            if (enem->makeMove(*direction))
            {
                ((map_.at(oldPos.second)).at(oldPos.first))->removeEnemy(enem);

                coord updatedCoord{enem->getPosition()};

                tile(enem->getPosition()).insertEnemy(enem);


                //pair<int, int> newPos = (*it)->getPosition();
                // Remove old position
                //for (auto it2 = enemies_[oldCoord.position].begin(); it2 != enemies_[oldCoord.position].end(); ++it2)
                //{
                //if (*it == *it2)
                //{
                //    enemies_[oldCoord.position].erase(it2);
                //   break;
                //}
                //}
                //insertEnemy(*it, newPos);
                //tile(oldPos).removeEnemy(*it);
                //cout
                // << "Made move to " << (*direction).second << endl;
                break;
            }
        }
    }
    return;
}

/**
 * Signature coord(pair<int, int>)
 * Purpose: Constructs coordinate from a pair of integers
 */
Map::coord::coord(std::pair<int, int> xy) : position{std::to_string(xy.first) +
                                                     "$" + std::to_string(xy.second)},
                                            x_{xy.first}, y_{xy.second} {}

/**
 * Signature: corrd(int, int)
 * Purpose: Constructs coordinate from individual coordinate data
 */
Map::coord::coord(int x, int y) : position{std::to_string(x) + "$" + std::to_string(y)},
                                  x_{x}, y_{y} {}

/**
 * Signature: coord(string)
 * Purpose: Constructs coordinate from a string of the coordinate data
 */
Map::coord::coord(string xy) : position{xy}, x_{stoi(xy.substr(0, xy.find("$")))},
                               y_{stoi(xy.substr((xy.find("$") + 1), std::string::npos))} {}

/**
 * Signature: vector<shared_ptr<Item>> pickupItems(int, int)
 * Purpose: Empties the specified tile of all tiles and provides all items
 */
vector<shared_ptr<Item>> Map::pickUpItems(int x, int y)
{
    return ((map_.at(y)).at(x))->pickupItems();
}

/**
 * Signature: int getNumWalls()
 * Purpose: Provides the number of wall tiles in a map
 */
int Map::getNumWalls()
{
    return num_wall_;
}

/**
 * Signature: int getNumExits()
 * Purpose: Provides the number of exit tiles in a map
 */
int Map::getNumExits()
{
    return num_exit_;
}

/**
 * Signature: int getNumSpaces()
 * Purpose: Provides the number of space tiles in a map
 */
int Map::getNumSpaces()
{
    return num_space_;
}

/**
 * Signature: pair<int, int> findNextEmpty(pair<int, int>)
 * Purpose: Finds the nearest available tile on the map
 */
pair<int, int> Map::findNextEmpty(pair<int, int> input)
{
    coord currentPlayer = coord{player_->getPosition()};
    while (true)
    {
        // If we are at an available tile, return the position
        if ((((map_.at(input.second)).at(input.first))->available()) &&
            !((input.first == currentPlayer.x_) && (input.second == currentPlayer.y_)))
        {
            return input;
        }
        // Increase the column index if possible
        else if (static_cast<size_t>(input.first) < ((map_.at(input.second)).size() - 1))
        {
            input.first++;
        }
        // Increase the row index and set column to zero otherwise
        else if (static_cast<size_t>(input.second) < (map_.size() - 1))
        {
            input.first = 0;
            input.second++;
        }
        // Go back to the top-left corner if both are exhausted
        else
        {
            input.first = input.second = 0;
        }
    }
}

/**
 * Signature: bool checkExit(pair<int, int>)
 * Purpose: Determines if a specified tile is an exit tile
 */
bool Map::checkExit(pair<int, int> tile_location)
{
    int colour = ((map_.at(tile_location.second)).at(tile_location.first))->getColour();
    return (colour == GameColours::Green);
}

/**
 * Signature: void clearMap()
 * Purpose: Clears map of all enemies and items
 */
void Map::clearMap()
{
    items_.clear();
    enemies_.clear();
    current_ = start_;

    for (auto row = map_.begin(); row != map_.end(); ++row)
    {
        for (auto tile = (*row).begin(); tile != (*row).end(); ++tile)
        {
            (*tile)->clearTile();
        }
    }
}

vector<shared_ptr<Enemy>> &Map::getEnemies()
{
    return enemies_;
}