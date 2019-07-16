#include "Entity.h"
#include "Consumable.h"
#include "Equipable.h"
#include "Map.h"
#include "Player.h"
#include "Mage.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

// Declare enemy name
const string Mage::ENTITY_NAME = "Mage";

/**
 * Signature: Mage(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial mage's health, energy, and position
 */
Mage::Mage(int teleport, double health, double energy, double attack, double armour, pair<int, int> position,
           vector<shared_ptr<Consumable>> consumables = {}, 
           vector<shared_ptr<Equipable>> equipables = {}) : teleport_amount_{teleport},
           Player{health, energy, attack, armour, position, consumables, equipables} {}

/**
 * Signature: bool useSpecial(pair<int, int>)
 * Purpose: Utilizes special move to specified location if possible
 * Note: Returns false if special move was unsuccessful, and true otherwise
 */
bool Mage::useSpecial(pair<int, int> location) {
    if(((abs(location.first - position_.first) <=  teleport_amount_) &&
       ((location.second - position_.second) == 0)) || 
       ((abs(location.second - position_.second) <=  teleport_amount_) &&
       ((location.first - position_.first) == 0)) && 
       (current_map_->tile(location.first, location.second).available()) &&
       (this->specialReady())) {
           position_ = location;
           return true;
    }

    return false;
}

/**
 * Signature: vector<pair<int, int>> specialMoves()
 * Purpose: Provides a collection of coordinates that can be moved to under a special move
 * Note: This is an expensive operation, taking O(max{Row, Column}) time
 */
vector<pair<int, int>> Mage::specialMoves() {
    vector<pair<int, int>> special_moves = {};
    
    for(int teleport = 1; teleport <= teleport_amount_; teleport++) {
        
        // Determine if a teleport in the right direction is possible
        if(((position_.first + teleport) < current_map_->numColumns()) &&
           (current_map_->tile((position_.first + teleport), position_.second).available())) {
            special_moves.emplace_back((position_.first + teleport), position_.second);
        }
        
        // Determine if a teleport in the left direction is possible
        if(((position_.first - teleport) >= 0) &&
           (current_map_->tile((position_.first - teleport), position_.second).available())) {
            special_moves.emplace_back((position_.first - teleport), position_.second);
        }

        // Determine if a teleport in the up direction is possible
        if(((position_.second + teleport) < current_map_->numRows(position_.first)) &&
           (current_map_->tile(position_.first, (position_.second + teleport)).available())) {
            special_moves.emplace_back(position_.first, (position_.second + teleport));
        }

        // Determine if a teleport in the down direction is possible
        if(((position_.second - teleport) >= 0) &&
           (current_map_->tile(position_.first, (position_.second + teleport)).available())) {
            special_moves.emplace_back(position_.first, (position_.second - teleport));
        }
    }

    return special_moves;
}

/**
 * Signature: string getName()
 * Purpose: Provides name of mage
 */
string Mage::getName() {
    return "mage";
}
