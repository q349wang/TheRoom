#include "Player.h"
#include "Entity.h"
#include "Consumable.h"
#include "Equipable.h"
#include "Map.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

/**
 * Signature: Player(double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial player's health, energy, and position
 */
Player::Player(double health, double energy, double attack, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables = {}, 
               vector<shared_ptr<Equipable>> equipables = {}) :
               Entity{health, energy, attack, position, consumables, equipables} {}

/**
 * Signature: void decreaseCooldown()
 * Purpose: Decreases the cooldown after every specified turn
 */
void Player::decreaseCooldown() {
    if(cooldown_ > BASE_SPECIAL_READY) {
        cooldown_--;
    }
}

/**
 * Signature: void resetCooldown()
 * Purpose: Resets the cooldown of a Player's special movement
 */
void Player::resetCooldown() {
    cooldown_ = BASE_SPECIAL_COOLDOWNN;
}

/**
 * Signature: specialReady()
 * Purpose: Determines if Player's special movement is a
 */
bool Player::specialReady() {
    return (cooldown_ == BASE_SPECIAL_READY);
}

/**
 * Signature: bool checkMove(pair<int, int>)
 * Purpose: Determines if a provided move is possible for a player
 */
bool Player::checkMove(pair<int, int> location) {
    if(location.first >= 0  && location.first < current_map_->numColumns()) {
        if(location.second >= 0 && location.second < current_map_->numRows()) {
            if((abs(location.first - position_.first) <= 1) && 
               (abs(location.second - position_.second) <= 1)) {
                   if(current_map_->tile().available()) {
                       return true;
                   }
               }
        }
    }

    return false;
}

/**
 * Signature: bool makeMove(char)
 * Purpose: Makes a move in a specified direction (indicated using 'R', 'L', 'U' 'D')
 *          If move was valid, returns true, otherwise remains stationary and returns false
 */
bool Player::makeMove(char direction) {
    pair<int, int> updated_position = position_;

    switch(direction) {
        case 'R':
            updated_position.first++;
        case 'L':
            updated_position.first--;
        case 'U':
            updated_position.second++;
        case 'D':
            updated_position.second--;
        default:
            // Return false if any other input is detected!
            return false;
    }

    if(checkMove(updated_position)) {
        updatePosition(updated_position);
        return true;
    }

    return false;
}

/**
 * Signature: void consumeConsumable(shared_ptr<Consumable>);
 * Purpose: Utilizes a specified consumable item
 */
void Player::consumeConsumable(string consume_name) {
    for(auto& existing_consume: consumables_) {
        if(consume_name == existing_consume->getName()) {
            existing_consume->useItem(); // TODO implement use item functionality 
        }
    }
}

/**
 * Signature: void pickUpItems()
 * Purpose: Picks up all items stored on its current tile, and empties tile
 */
void Player::pickUpItems() {
    // TODO
}

/**
 * Signature: Ranger(double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial ranger's health, energy, and position
 */
Ranger::Ranger(double health, double energy, double attack, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables = {}, 
               vector<shared_ptr<Equipable>> equipables = {}) :
               Player{health, energy, attack, position, consumables, equipables} {}

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
    if((position_.first + right) < current_map_->numColumns()) {
        while(!(current_map_->tile((position_.first + right), position_.second).available())) {
            if((position_.first + right) < (current_map_->numColumns() - 1)) {
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
    if((position_.second + up) < (current_map_->numRows(position_.first))) {
        while(current_map_->tile(position_.first, (position_.second + up)).available()) {
            if((position_.second + up) < (current_map_->numRows(position_.first) - 1)) {
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
    if(((position_.first + right) < current_map_->numColumns()) && 
       (current_map_->tile((position_.first + right), position_.second).available())) {
        special_moves.emplace_back((position_.first + right), position_.second);
    }
    else if(((position_.first - left) >= 0) && 
            (current_map_->tile((position_.first - left), position_.second).available())) {
        special_moves.emplace_back((position_.first - (left - 1)), position_.second);
    }
    else if(((position_.second + up) < current_map_->numRows(position_.first)) && 
            (current_map_->tile(position_.first, (position_.second + up)).available())) {
        special_moves.emplace_back(position_.first, (position_.second + (up - 1)));
    }
    else if(((position_.second - down) >= 0) && 
            (current_map_->tile(position_.first, (position_.second - down)).available())) {
        special_moves.emplace_back(position_.first, (position_.second - (down - 1)));
    }
    
    return special_moves;

}

/**
 * Signature: Mage(double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial mage's health, energy, and position
 */
Mage::Mage(int teleport, double health, double energy, double attack, pair<int, int> position,
           vector<shared_ptr<Consumable>> consumables = {}, 
           vector<shared_ptr<Equipable>> equipables = {}) : teleport_amount_{teleport},
           Player{health, energy, attack, position, consumables, equipables} {}

/**
 * Signature: bool useSpecial(pair<int, int>)
 * Purpose: Utilizes special move to specified location if possible
 * Note: Returns false if special move was unsuccessful, and true otherwise
 */
bool Mage::useSpecial(pair<int, int> location) {
    if(((abs(location.first - position_.first) ==  teleport_amount_) &&
       ((location.second - position_.second) == 0)) || 
       ((abs(location.second - position_.second) ==  teleport_amount_) &&
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

    // Determine if a teleport in the right direction is possible
    if(((position_.first + teleport_amount_) < current_map_->numColumns()) &&
       (current_map_->tile((position_.first + teleport_amount_), position_.second).available())) {
        special_moves.emplace_back((position_.first + teleport_amount_), position_.second);
    }

    // Determine if a teleport in the left direction is possible
    else if(((position_.first - teleport_amount_) >= 0) &&
            (current_map_->tile((position_.first - teleport_amount_), position_.second).available())) {
        special_moves.emplace_back((position_.first - teleport_amount_), position_.second);
    }

    // Determine if a teleport in the up direction is possible
    else if(((position_.second + teleport_amount_) < current_map_->numRows(position_.first)) &&
            (current_map_->tile(position_.first, (position_.second + teleport_amount_)).available())) {
        special_moves.emplace_back(position_.first, (position_.second + teleport_amount_));
    }

    // Determine if a teleport in the down direction is possible
    else if(((position_.second - teleport_amount_) >= 0) &&
            (current_map_->tile(position_.first, (position_.second + teleport_amount_)).available())) {
        special_moves.emplace_back(position_.first, (position_.second - teleport_amount_));
    }

    return special_moves;
}

/**
 * Signature: Warrior(double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial warrior's health, energy, and position
 */
Warrior::Warrior(double health, double energy, double attack, pair<int, int> position,
                 vector<shared_ptr<Consumable>> consumables = {}, 
                 vector<shared_ptr<Equipable>> equipables = {}) :
                 Player{health, energy, attack, position, consumables, equipables} {}


/**
 * Signature: bool useSpecial(pair<int, int>)
 * Purpose: Utilizes special move to specified location if possible
 * Note: Returns false if special move was unsuccessful, and true otherwise
 */
bool Warrior::useSpecial(pair<int, int> location) {
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
vector<pair<int, int>> Warrior::specialMoves() {
    vector<pair<int, int>> special_moves = {};
    int right = 0, left = 0, up = 0, down = 0;

    // Determine the first wall or non-existent tile from the 
    // current position in the right direction
    while(current_map_->tile((position_.first + right), position_.second).available()) {
        if((position_.first + right) < (current_map_->numColumns() - 1)) {
            right++;
        }
        else {
            right++;
            break;
        }
    }

    // Determine the first wall or non-existent tile from the 
    // current position in the left direction
    while(current_map_->tile((position_.first - left), position_.second).available()) {
        if((position_.first - left) > 0) {
            left++;
        }
        else {
            left++;
            break;
        }
    }    

    // Determine the first wall or non-existent tile from the 
    // current position in the up direction
    while(current_map_->tile(position_.first, (position_.second + up)).available()) {
        if((position_.second + up) < (current_map_->numRows(position_.first) - 1)) {
            up++;
        }
        else {
            up++;
            break;
        }
    }

    // Determine the first wall or non-existent tile from the 
    // current position in the up direction
    while(current_map_->tile(position_.first, (position_.second - down)).available()) {
        if((position_.second - down) > 0) {
            down++;
        }
        else {
            down++;
            break;
        }
    }

    // Insert the furthest available tile from the current tile position
    if(right != 1) {
        special_moves.emplace_back((position_.first + (right - 1)), position_.second);
    }
    else if(left != 1) {
        special_moves.emplace_back((position_.first - (left - 1)), position_.second);
    }
    else if(up != 1) {
        special_moves.emplace_back(position_.first, (position_.second + (up - 1)));
    }
    else if(down != 1) {
        special_moves.emplace_back(position_.first, (position_.second - (down - 1)));
    }
    
    return special_moves;
}