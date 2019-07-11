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
    for(auto& existing_items: equipables_) {
        
    }
}

/**
 */
void attack(Enemy*) {

}

/**
 */
bool checkMove(std::vector<int>) {

}

/**
 */
void takeDamage(double) {

}

/**
 */
void useEnergy(double) {

}

/**
 */
bool isDead() {

}
