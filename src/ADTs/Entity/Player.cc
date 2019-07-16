#include "Player.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

/**
 * Signature: Player(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial player's health, energy, and position
 */
Player::Player(double health, double energy, double attack, double armour, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables, 
               vector<shared_ptr<Equipable>> equipables) :
               Entity{health, energy, attack, armour, position, consumables, equipables} {}

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
 * Signature: int getCooldown()
 * Purpose: Provides the current special movement cooldown
 */
int Player::getCooldown() {
    return cooldown_;
}

/**
 * Signature: bool checkMove(char)
 * Purpose: Determines if a provided move is possible for a player
 *          Utilizes 'N', 'E', 'S', 'W' for direction indication
 */
bool Player::checkMove(char direction) {
    pair<int, int> updated_position = position_;

    // Update the modified position dependent on the input direction
    switch(direction) {
        case 'E':
            updated_position.first++; 
        case 'W':
            updated_position.first--;
        case 'N':
            updated_position.second++;
        case 'S':
            updated_position.second--;
        default:
            return false;
    }

    if(updated_position.first >= 0  && updated_position.first < current_map_->numColumns()) {
        if(updated_position.second >= 0 && updated_position.second < current_map_->numRows(updated_position.first)) {    
            if(current_map_->tile(updated_position.first, updated_position.second).available()) {
                    return true;
            }
        }
    }

    return false;
}

/**
 * Signature: bool makeMove(char)
 * Purpose: Makes a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
 *          If move was valid, returns true, otherwise remains stationary and returns false
 */
bool Player::makeMove(char direction) {
    pair<int, int> updated_position = position_;

    switch(direction) {
        case 'E':
            updated_position.first++;
        case 'W':
            updated_position.first--;
        case 'N':
            updated_position.second++;
        case 'S':
            updated_position.second--;
        default:
            // Return false if any other input is detected!
            return false;
    }

    if(checkMove(direction)) {
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
            existing_consume->useItem(consume_name); // TODO implement use item functionality 
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