#include "Entity.h"
#include<vector>

using namespace std;

/**
 */
double Entity::getHealth() {
    return health_;
}

/**
 */
double Entity::getEnergy() {
    return energy_;
}

/**
 */
double Entity::getAttack() {
    return attackStrength_;
}

/**
 */
pair<int,int> Entity::getPosition() {
    return position_;
}

/**
 */
void Entity::addEquipable(Equipable& new_equip) {
    equipables_.emplace_back(&new_equip);
}

/**
 */    
void Entity::addConsumable(Consumable& new_consume) {
    consumables_.emplace_back(&new_consume);
}

/**
 */
void Entity::equipEquipable(Equipable& equip_item) {
    for(auto& existing_item: equipables_) {
        if(existing_item == &equip_item) {
            //TODO
        }
    }
}

/**
 */
const std::vector<Equipable*>& Entity::currentEquipables() {
    return equipables_;
}

/**
 */
const std::vector<Consumable*>& Entity::currentConsumables() {
    return consumables_;
}

/**
 */
void Entity::attack(Entity* enemy) {
    enemy->takeDamage(attackStrength_);
}

/**
 */
bool Entity::checkMove(pair<int,int>) {
    //TODO
}

/**
 */
void Entity::takeDamage(double damage) {
    health_ =  health_ - damage;
}

/**
 */
void Entity::useEnergy(double energy) {
    energy_ = energy_ - energy;
}

/**
 */
bool Entity::isDead() {
    return (health_ <= BASE_HEALTH_ENERGY) ? (true) : (false);
}

/**
 */
bool Entity::isOutOfEnergy() {
    return (energy_ <= BASE_HEALTH_ENERGY) ? (true) : (false);
}
