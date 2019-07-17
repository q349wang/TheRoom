#include "Player.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

#include <vector>
#include <memory>
#include <utility>
#include <iostream>


using namespace std;

/**
 * Signature: Player(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires initial player's health, energy, and position
 */
Player::Player(double health, double energy, double attack, double armour, 
               string name, pair<int, int> position, 
               vector<shared_ptr<Consumable>> consumables, 
               vector<shared_ptr<Equipable>> equipables) :
               Entity{health, energy, attack, armour, name, position, consumables, equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Default Destructor
 */
Player::~Player() {}

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
    cooldown_ = BASE_SPECIAL_COOLDOWN;
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
            break;

        case 'W':
            updated_position.first--;
            break;

        case 'N':
            updated_position.second--;
            break;

        case 'S':
            updated_position.second++;
            break;

        default:
            return false;
    }

    if(updated_position.second >= 0  && updated_position.second < current_map_->numRows()) {
        if(updated_position.first >= 0 && updated_position.first < current_map_->numColumns(updated_position.second)) {    
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
            break;

        case 'W':
            updated_position.first--;
            break;

        case 'N':
            updated_position.second--;
            break;

        case 'S':
            updated_position.second++;
            break;

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
void Player::consumeConsumable(shared_ptr<Entity> entity, string consume_name) {
    vector<shared_ptr<Consumable>> consumables = (entity->currentConsumables());

    for(auto existing = consumables.begin(); existing != consumables.end(); ++existing) {
        if(consume_name == (*existing)->getName()) {
            map<string, StatMod> consume_mods = (*existing)->useItem();
            for(auto it = consume_mods.begin(); it != consume_mods.end(); ++it) {
                entity->applyStat((*it).first, (*it).second);
            }

            consumables.erase(existing);
            break;
        }
    }
}

/**
 * Signature: void equipEquipable(shared_ptr<Equipable>);
 * Purpose: Utilizes a specified equipable item
 */
void Player::equipEquipable(shared_ptr<Entity> entity, string equip_name) {
    vector<shared_ptr<Equipable>> equipables = (entity->currentEquipables());

    for(auto existing = equipables.begin(); existing != equipables.end(); ++existing) {
        if(equip_name == (*existing)->getName()) {
            map<string, StatMod> equip_mods = (*existing)->useItem();
            for(auto it = equip_mods.begin(); it != equip_mods.end(); ++it) {
                entity->applyStat((*it).first, (*it).second);
            }

            break;
        }
    }
}

/**
 * Signature: void dropEquipable(string)
 * Purpose: Drops a specified equipable item
 */
void Player::dropEquipable(string equip_name) {
    for(auto existing = equipables_.begin(); existing != equipables_.end(); ++existing) {
        if(equip_name == (*existing)->getName()) {

            map<string, StatMod> equip_mods = (*existing)->getPassive();
            for(auto it = equip_mods.begin(); it != equip_mods.end(); ++it) {
                reverseStat((*it).first, (*it).second);
            }

            equipables_.erase(existing);
            break;
        }
    }
}

/**
 * Signature: void reverseStat(string, StatMod)
 * Purpose: Reverses the stat mods implications for a player
 */
void Player::reverseStat(string stat, StatMod mod) {
    if(mod.getMultiplier() != 0) {
        if(stat == "Ranger" || stat == "Mage" || stat == "Warrior") {
            if(stat == getName()) {
                armour_ = ((armour_)/mod.getMultiplier()) - mod.getAdder();
                health_ = ((health_)/mod.getMultiplier()) - mod.getAdder();
                energy_ = ((energy_)/mod.getMultiplier()) - mod.getAdder();
                attackStrength_ = ((attackStrength_)/mod.getMultiplier()) - mod.getAdder();
            }
        }

        else {
            if(stat == "Health") {
                health_ = ((health_)/mod.getMultiplier()) - mod.getAdder();
            }
            else if(stat == "Attack") {
                attackStrength_ = ((attackStrength_)/mod.getMultiplier()) - mod.getAdder();
            }
            else if(stat == "Damage") {
                health_ = ((health_)/mod.getMultiplier()) + mod.getAdder();
            }
            else if(stat == "Energy") {
                energy_ = ((energy_ )/mod.getMultiplier()) - mod.getAdder();
            }   
            else if(stat == "Armor") {
                armour_ = ((armour_)/mod.getMultiplier()) - mod.getAdder();
            }
        }   
    }
}

/**
 * Signature: void addEquipable(shared_ptr<Equipable>)
 * Purpose: Equips equipable and activates passive stat mods
 */
void Player::addEquipable(shared_ptr<Equipable> equip) {
    map<string, StatMod> passive_mods = equip->getPassive();
    for(auto it = passive_mods.begin(); it != passive_mods.end(); ++it) {
        applyStat((*it).first, (*it).second);
    }

    equipables_.emplace_back(equip);
}

/**
 * Signature: void pickUpItems()
 * Purpose: Picks up all items stored on its current tile, and empties tile
 */
vector<shared_ptr<Item>> Player::pickUpItems() {
    return current_map_->pickUpItems(position_.first, position_.second);
}