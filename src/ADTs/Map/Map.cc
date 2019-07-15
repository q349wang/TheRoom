#include "Map.h"
#include "Tile.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

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
        
        // Iterate through the provided map specifications to construct map tiles
        for(auto row = map.begin; row != map.end(); ++row) {
            vector<shared_ptr<Tile>> column = {};
            for(auto col = row->begin(); col != row->end(); ++col) {
                // If the tile is marked as 'E' it is assumed to be an exit tile
                if(col == 'E') {
                    column.emplace_back(make_shared<Tile>(ExitTile{}));
                    exits_.emplace(coord{(row - map.begin), (col - row->begin())}.position, column.back());
                }
                // If the tile is marked as 'W' it is assumed to be an wall tile   
                else if (col == 'W') {
                    column.emplace_back(make_shared<Tile>(WallTile{}));
                } 
                // Any other input is assumed to be a basic space tile
                else {
                    column.emplace_back(make_shared<Tile>(SpaceTile{})); 
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
        map_[location.x_][location.y_].get()->insertItem(item);
        
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
        map_[location.x_][location.y_]->insertEnemy(enemy);
        enemies_.emplace(location.position, enemy);

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
        return *map_[x][y];
    }