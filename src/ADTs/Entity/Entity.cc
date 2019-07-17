#include "Entity.h"
#include "../Map/Map.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

/**
 * Signature: Entity(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial entity's health, energy, and position
 */
Entity::Entity(double health, double energy, double attack, double armour, 
               string name, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables,
               vector<shared_ptr<Equipable>> equipables) :
               health_{health}, energy_{energy}, attackStrength_{attack}, armour_{armour},
                name_{name}, position_{position}, consumables_{consumables_}, 
               equipables_{equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Defualt Destructor
 */
Entity::~Entity(){}

// Base health and energy
const double Entity::BASE_HEALTH_ENERGY = 0.0;

/**
 * Signature: double getHealth()
 * Purpose: Provides an entity's current health
 */
double Entity::getHealth() {
    return health_;
}

/**
 * Signature: double getEnergy()
 * Purpose: Provides an entity's current energy
 */
double Entity::getEnergy() {
    return energy_;
}

/**
 * Signature: double getAttack()
 * Purpose: Provides an entity's current attack
 */
double Entity::getAttack() {
    return attackStrength_;
}

/**
 * Signature dobule getArmour()
 * Purpose: Provides an entity's current armour
 */
double Entity::getArmour() {
    return armour_;
}

/**
 * Signature: pair<int, int> getPosition()
 * Purpose: Provides an entity's current position
 */
pair<int,int> Entity::getPosition() {
    return position_;
}

/**
 * Signature: void addEquipable(shared_ptr<Equipable>)
 * Purpose: Adds equipable to current collection
 */
void Entity::addEquipable(shared_ptr<Equipable> new_equip) {
    equipables_.emplace_back(new_equip);
}

/**
 * Signature: void addConsumable(shared_ptr<Equipable>)
 * Purpose: Adds equipable to current collection
 */    
void Entity::addConsumable(shared_ptr<Consumable> new_consume) {
    consumables_.emplace_back(new_consume);
}

/**
 * Signature: const vector<shared_ptr<Equipable>>& currentEquipables()
 * Purpose: Provides a const reference to all the current equipables
 */
vector<shared_ptr<Equipable>>& Entity::currentEquipables() {
    return equipables_;
}

/**
 * Signature: const vector<shared_ptr<Consumable>>& currentConsumable()
 * Purpose: Provides a const reference to all the current consumables
 */
vector<shared_ptr<Consumable>>& Entity::currentConsumables() {
    return consumables_;
}

/**
 * Signature: double attack(shared_ptr<Entity>)
 * Purpose: Performs attack on a specified entity
 *          Additionally returns the attack amount
 */
double Entity::attack(shared_ptr<Entity> enemy) {
    if(!isOutOfEnergy()) {
        return enemy->takeDamage(attackStrength_);
    }
}

/**
 * Signature: void takeDamage(double)
 * Purpose: Reduces the health of the current entity by a specified amount
 *          Additionally returns actual damage taken, skewed by armour
 */
double Entity::takeDamage(double damage) {
    double weighted_damage = (double) (100.0/(100.0 + armour_)) * damage;
    health_ =  health_ - weighted_damage;
    return weighted_damage;
}

/**
 * Signature: void useEnergy(double energy)
 * Purpose: Reduces the energy of the current entity by a specified amount
 */
void Entity::useEnergy(double energy) {
    energy_ = energy_ - energy;
}

/**
 * Signature: bool isDead()
 * Purpose: Determines if the current entity is considered inactive (dead)
 */
bool Entity::isDead() {
    return (health_ <= BASE_HEALTH_ENERGY) ? (true) : (false);
}

/**
 * Signature: bool isOutOfEnergy()
 * Purpose: Determines if the current entity is considered out of energy
 */
bool Entity::isOutOfEnergy() {
    return (energy_ <= BASE_HEALTH_ENERGY) ? (true) : (false);
}

/**
 * Signature: void makeMove(pair<int, int>)
 * Purpose: Moves entity to specified location
 * Note: Does not check if move is valid or applicable to current map
 */
void Entity::updatePosition(pair<int, int> location) {
    position_ = location;
}

/**
 * Signature: string getName()
 * Purpose: Provides an entity's name
 */
string Entity::getName() {
    return name_;
}

/**
 * Signature: void applyStat(string, StatMod)
 * Purpose: Apply the specified stat mod
 */
void Entity::applyStat(string stat, StatMod mod) {
    if(stat == "Ranger" || stat == "Mage" || stat == "Warrior") {
        if(stat == getName()) {
            armour_ = (armour_ + mod.getAdder()) * mod.getMultiplier();
            health_ = (health_ + mod.getAdder()) * mod.getMultiplier();
            energy_ = (energy_ + mod.getAdder()) * mod.getMultiplier();
            attackStrength_ = (attackStrength_ + mod.getAdder()) * mod.getMultiplier();
        }
    }

    else {
        if(stat == "Health") {
            health_ = (health_ + mod.getAdder()) * mod.getMultiplier();
        }
        else if(stat == "Attack") {
            attackStrength_ = (attackStrength_ + mod.getAdder()) * mod.getMultiplier();
        }
        else if(stat == "Damage") {
            health_ = (health_ - mod.getAdder()) * mod.getMultiplier();
        }
        else if(stat == "Energy") {
            energy_ = (energy_ + mod.getAdder()) * mod.getMultiplier();
        }   
        else if(stat == "Armor") {
            armour_ = (armour_ + mod.getAdder()) * mod.getMultiplier();
        }
    }
}

/**
 * Signature: void setMap(shared_ptr<Map>)
 * Purpose: Sets the map of an entity
 */
void Entity::setMap(shared_ptr<Map> map) {
    current_map_ = map;
}

/**
 * Signature: bool dropItems(string)
 * Purpose: Drops first instance of item specified by provided name
 */
bool Entity::dropItem(string name) {
    for(auto it = consumables_.begin(); it != consumables_.end(); ++it) {
        if((*it)->getName() == name) {
            consumables_.erase(it);
            return true;
        }
    }

    for(auto it = equipables_.begin(); it != equipables_.end(); ++it) {
        if((*it)->getName() == name) {
            equipables_.erase(it);
            return true;
        }
    }

    return false;
}

/**
 * Signature: void dropAllItems()
 * Purpose: Drops all items onto current tile
 */
void Entity::dropAllItems() {
    for(auto it = consumables_.begin(); it != consumables_.end(); ++it) {
        current_map_->insertItem(*it, position_);
    }

    for(auto it = equipables_.begin(); it != equipables_.end(); ++it) {
        current_map_->insertItem(*it, position_);
    }

    consumables_.clear();
    equipables_.clear();
}
