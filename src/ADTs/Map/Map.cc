#include "Map.h"
#include "Tile.h"
#include "ExitTile.h"
#include "SpaceTile.h"
#include "WallTile.h"

#include "Enemy.h"
#include "Player.h"
#include "Item.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

    /**
     * Signature: Map(shared_ptr<Player>, vector<vector<char>>, pair<int, int>, unordered_map<string, 
     *                shared_ptr<Item>>, unordered_map<string, shared_ptr<Enemy>>)
     * Purpose: Constructs map with a specified player, map layout, start tile, and any pre-existing enemies/items
     */
    Map::Map(shared_ptr<Player> player, vector<vector<char>> map, 
       pair<int, int> start = {0,0},    
       unordered_map<string, vector<shared_ptr<Item>>> items = {},
       unordered_map<string, vector<shared_ptr<Enemy>>> enemies = {}) : start_{start}, current_{start}, player_{player}, 
                                                                items_{items}, enemies_{enemies} {
        
        vector<shared_ptr<Tile>> column = {};
            
        // Iterate through the provided map specifications to construct map tiles
        for(auto row = map.begin; row != map.end(); ++row) {
            for(auto col = row->begin(); col != row->end(); ++col) {
                // If the tile is marked as 'E' it is assumed to be an exit tile
                if(col == 'E') {
                    column.emplace_back(make_shared<ExitTile>(ExitTile{}));
                    exits_.emplace(coord{(row - map.begin), (col - row->begin())}.position, column.back());
                }
                // If the tile is marked as 'W' it is assumed to be an wall tile   
                else if (col == 'W') {
                    column.emplace_back(make_shared<WallTile>(WallTile{}));
                } 
                // Any other input is assumed to be a basic space tile
                else {
                    column.emplace_back(make_shared<SpaceTile>(SpaceTile{})); 
                }
            }
            map.emplace_back(column);
            column.clear();
        }
    }
    
    /**
    * Signature: void insertItem(shared_ptr<Item>, pair<int, int>) : void
    * Purpose: Inserts provided item at specified location on the map
    */
    void Map::insertItem(shared_ptr<Item> item, pair<int, int> coordinates) {
        coord location = coord{coordinates};
        ((map_.at(location.x_)).at(location.y_))->insertItem(item);
        
        if(items_.find(location.position) == items_.end()) {
            items_.emplace(location.position, vector<shared_ptr<Item>>{item});
        } 
        else {
            items_[location.position].emplace_back(item);
        }
    }

    /**
     * Signature: void Map(shared_ptr<Player>, vector<vector<char>>, pair<int, int>, unordered_map<string, 
     *                shared_ptr<Item>>, unordered_map<string, shared_ptr<Enemy>>)
     * Purpose:JHKGJKHKJHJKHKJHJKHKJH Constructs map with a specified player, map layout, start tile, and any pre-existing enemies/items
     */
    void Map::insertEnemy(shared_ptr<Enemy> enemy, pair<int, int> coordinates) {
        coord location = coord{coordinates};
        ((map_.at(location.x_)).at(location.y_))->insertEnemy(enemy);
        
        if(enemies_.find(location.position) == enemies_.end()) {
            enemies_.emplace(location.position, vector<shared_ptr<Enemy>>{enemy});
        } 
        else {
            enemies_[location.position].emplace_back(enemy);
        }
    }

    /**
     * Signature: int numColumns()
     * Purpose: Provides the number of columns within the map
     */
    int Map::numColumns() {
        return map_.size();
    }

    /**
     * Signature: int numRows(int)
     * Purpose: Provides the number of rows at a specified column 
     */
    int Map::numRows(int column) {
        return map_[column].size();
    }

    /**
     * Signature: const Tile& tile(int, int)
     * Purpose: Provides a const reference to a specified tile
     */
    const Tile& Map::tile(int x, int y) {
        return *((map_.at(x)).at(y));
    }

    /**
     * Signature: const vector<vector<shared_ptr<Tile>>>& getMap()
     * Purpose: Provides a const reference to the current map
     */
    const vector<vector<shared_ptr<Tile>>>& Map::getMap() {
        return map_;
    }

    /**
     * Signature: void moveEnemies()
     * Purpose: Moves all enemies currently on the map towards the player
     */
    void Map::moveEnemies() {
        for (pair<string, vector<shared_ptr<Enemy>>> tile : enemies_) {
            coord position = coord{tile.first};
            vector<pair<int, char>> movement = {};
            
            int x_difference = current_.x_ - position.x_;
            int y_difference = current_.y_ - position.y_;

            if(x_difference >= 0) {
                movement.emplace_back(abs(x_difference - 1), 'E');
                movement.emplace_back((x_difference + 1), 'W');
            }
            else {
                movement.emplace_back((abs(x_difference) - 1), 'W');
                movement.emplace_back((abs(x_difference) + 1), 'E');
            }

            if(y_difference >= 0) {
                movement.emplace_back(abs(y_difference - 1), 'S');
                movement.emplace_back((y_difference + 1), 'N');
            } 
            else {
                movement.emplace_back((abs(y_difference) - 1), 'N');
                movement.emplace_back((abs(y_difference) + 1), 'S');
            }

            // Sort the movement directions
            sort(movement.begin(), movement.end());

            // Iterate through all enemies on the current tile, and all possible directions
            // In order of increasing distance, and make the move towards the closest location
            for(auto it = tile.second.begin(); it != tile.second.end(); ++it) {
                for(auto direction = movement.begin(); direction != movement.end(); ++direction) {
                    if((*it)->makeMove((*direction).second)) {
                        break;
                    }
                }
            }
        }
    }