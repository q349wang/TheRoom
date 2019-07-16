#include "Enemy.h"
#include "../Map/Map.h"

#include <memory>
#include <vector>
#include <utility>

using namespace std;

/**
 * Signature: Enemy(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial enemy's health, energy, and position
 */
Enemy::Enemy(double health, double energy, double attack, double armour, 
             pair<int, int> position, std::string name,
             vector<shared_ptr<Consumable>> consumables, 
             vector<shared_ptr<Equipable>> equipables) :
             Entity{health, energy, attack, armour, position, name, consumables, equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Defualt Destructor
 */
Enemy::~Enemy() {}

/**
 * Signature: void dropAllItems()
 * Purpose: Drops all enemy items onto current tile
 */
void Enemy::dropAllItems() {
    for(auto it = consumables_.begin(); it != consumables_.end(); ++it) {
        current_map_->insertItem(*it, position_);
    }

    for(auto it = equipables_.begin(); it != equipables_.end(); ++it) {
        current_map_->insertItem(*it, position_);
    }

    consumables_.clear();
    equipables_.clear();
}
