#include "Ranger.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

/**
 * Signature: Ranger(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial ranger's health, energy, and position
 */
Ranger::Ranger(double health, double energy, double attack, double armour, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables, 
               vector<shared_ptr<Equipable>> equipables) :
               Player{health, energy, attack, armour, "Ranger", position, consumables, equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Defualt Destructor
 */
Ranger::~Ranger() {}

/**
 * Signature: bool useSpecial(pair<int, int>)
 * Purpose: Utilizes special move to specified location if possible
 * Note: Returns false if special move was unsuccessful, and true otherwise
 */
bool Ranger::useSpecial(pair<int, int> location) {
    vector<pair<int, int>> potential = specialMoves();
    for(auto it = potential.begin(); it != potential.end(); ++it) {
        if(*it == location) {
            position_ = location;
            return true;
        }
    }

    return false;
}

/**
 * Signature: vector<pair<int, int>> specialMoves()
 * Purpose: Provides a collection of coordinates that can be moved to under a special move
 * Note: This is an expensive operation, taking O(max{Row, Column}) time
 */
vector<pair<int, int>> Ranger::specialMoves() {
    vector<pair<int, int>> special_moves = {};
    int right = 1, left = 1, up = 1, down = 1;

    // Determine the first wall or non-existent tile from the 
    // current position in the right direction
    if((position_.first + right) < current_map_->numColumns(position_.second)) {
        while(!(current_map_->tile((position_.first + right), position_.second).available())) {
            if((position_.first + right) < (current_map_->numColumns(position_.second) - 1)) {
                right++;
            }
            else {
                right++;
                break;
            }
        }
    }
    
    // Determine the first wall or non-existent tile from the 
    // current position in the left direction
    if((position_.first - left) >= 0) {
        while(current_map_->tile((position_.first - left), position_.second).available()) {
            if((position_.first - left) > 0) {
                left++;
            }
            else {
                left++;
                break;
            }
        }    
    }

    // Determine the first wall or non-existent tile from the 
    // current position in the up direction
    if((position_.second + up) < (current_map_->numRows())) {
        while(current_map_->tile(position_.first, (position_.second + up)).available()) {
            if((position_.second + up) < (current_map_->numRows() - 1)) {
                up++;
            }
            else {
                up++;
                break;
            }
        }
    }

    // Determine the first wall or non-existent tile from the 
    // current position in the up direction
    if((position_.second - down) >= 0) {
        while(current_map_->tile(position_.first, (position_.second - down)).available()) {
            if((position_.second - down) > 0) {
                down++;
            }
            else {
                down++;
                break;
            }
        }
    }

    // Insert the furthest available tile from the current tile position after an
    // immediate contigous block of wall tiles
    if(((position_.first + right) < current_map_->numColumns(position_.second)) && 
       (current_map_->tile((position_.first + right), position_.second).available())) {
        special_moves.emplace_back((position_.first + right), position_.second);
    }
    else if(((position_.first - left) >= 0) && 
            (current_map_->tile((position_.first - left), position_.second).available())) {
        special_moves.emplace_back((position_.first - (left - 1)), position_.second);
    }
    else if(((position_.second + up) < current_map_->numRows()) && 
            (current_map_->tile(position_.first, (position_.second + up)).available())) {
        special_moves.emplace_back(position_.first, (position_.second + (up - 1)));
    }
    else if(((position_.second - down) >= 0) && 
            (current_map_->tile(position_.first, (position_.second - down)).available())) {
        special_moves.emplace_back(position_.first, (position_.second - (down - 1)));
    }
    
    return special_moves;
}

int Ranger::getColour() { return col; }
