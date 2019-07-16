#include "Enemy.h"
#include "Entity.h"
#include "Consumable.h"
#include "Equipable.h"
#include "Ground.h"

#include <memory>
#include <vector>
#include <utility>

using namespace std;

/**
 * Signature: Ground(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial ground enemy's health, energy, and position
 */
Ground::Ground(double health, double energy, double attack, double armour, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables = {}, 
               vector<shared_ptr<Equipable>> equipables = {}) :
               Enemy{health, energy, attack, armour, position, consumables, equipables} {}

/**
 * Signature: bool makeMove(char)
 * Purpose: Makes a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
 *          If move was valid, returns true, otherwise remains stationary and returns false
 */
bool Ground::makeMove(char direction) {
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
            // Return false if any other input is detected
            return false;
    }

    if(checkMove(direction)) {
        updatePosition(updated_position);
        return true;
    }

    return false;
}

/**
 * Signature: string getName()
 * Purpose: Provides the name of the ground enemy
 */
string Ground::getName() {
    return "ground";
}
