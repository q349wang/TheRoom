#include "Enemy.h"

#include <memory>
#include <vector>
#include <utility>

using namespace std;

/**
 * Signature: Enemy(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial enemy's health, energy, and position
 */
Enemy::Enemy(double health, double energy, double attack, double armour, pair<int, int> position,
             vector<shared_ptr<Consumable>> consumables, 
             vector<shared_ptr<Equipable>> equipables) :
             Entity{health, energy, attack, armour, position, consumables, equipables} {}

Enemy::~Enemy() {}

/**
 * Signature: void dropAllItems()
 * Purpose: Drops all enemy items onto current tile
 */
void dropAllItems() {
    // TODO
}
