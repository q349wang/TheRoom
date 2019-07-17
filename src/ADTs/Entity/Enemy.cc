#include "Enemy.h"
#include "../Map/Map.h"

#include <memory>
#include <vector>
#include <utility>

using namespace std;

/**
 * Signature: Enemy(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires initial enemy's health, energy, and position
 */
Enemy::Enemy(double health, double energy, double attack, double armour, 
             std::string name, pair<int, int> position,
             vector<shared_ptr<Consumable>> consumables, 
             vector<shared_ptr<Equipable>> equipables) :
             Entity{health, energy, attack, armour, name, position, consumables, equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Default Destructor
 */
Enemy::~Enemy() {}