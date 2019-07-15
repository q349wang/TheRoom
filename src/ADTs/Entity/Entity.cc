#include "Consumable.h"
#include "Equipable.h"
#include "Map.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

/**
 * Signature: Entity(double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial entity's health, energy, and position
 */
Entity::Entity(double health, double energy, double attack, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables = {}, 
               vector<shared_ptr<Equipable>> equipables = {}) :
               health_{health}, energy_{energy}, attackStrength_{attack},
               position_{position}, consumables_{consumables_}, 
               equipables_{equipables} {}

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
 * Signature: void equipEquipable(shared_ptr<Equipable>);
 * Purpose: Utilizes a specified equipable item
 */
void Entity::equipEquipable(string equip_name) {
    for(auto& existing_equip: equipables_) {
        if(equip_name == existing_equip->getName()) {
            existing_equip->useItem(); // TODO implement use item functionality 
        }
    }
}

/**
 * Signature: const vector<shared_ptr<Equipable>>& currentEquipables()
 * Purpose: Provides a const reference to all the current equipables
 */
const vector<shared_ptr<Equipable>>& Entity::currentEquipables() {
    return equipables_;
}

/**
 * Signature: const vector<shared_ptr<Consumable>>& currentConsumable()
 * Purpose: Provides a const reference to all the current consumables
 */
const vector<shared_ptr<Consumable>>& Entity::currentConsumables() {
    return consumables_;
}

/**
 * Signature: double attack(shared_ptr<Entity>)
 * Purpose: Performs attack on a specified entity
 *          Additionally returns the attack amount
 */
double Entity::attack(shared_ptr<Entity> enemy) {
    enemy->takeDamage(attackStrength_);
    return attackStrength_;
}

/**
 * Signature: void takeDamage(double)
 * Purpose: Reduces the health of the current entity by a specified amount
 */
void Entity::takeDamage(double damage) {
    health_ =  health_ - damage;
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
