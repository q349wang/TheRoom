#include "Ground.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

#include <memory>
#include <vector>
#include <utility>

using namespace std;

/**
 * Signature: Ground(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial ground enemy's health, energy, and position
 */
Ground::Ground(double health, double energy, double attack, double armour, 
               pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables,
               vector<shared_ptr<Equipable>> equipables) : 
               Enemy{health, energy, attack, armour, position, "Ground", consumables, equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Defualt Destructor
 */
Ground::~Ground(){}

/**
 * Signature: bool makeMove(char)
 * Purpose: Makes a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
 *          If move was valid, returns true, otherwise remains stationary and returns false
 */
bool Ground::makeMove(char direction)
{
    pair<int, int> updated_position = position_;

    switch (direction)
    {
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

    if (checkMove(direction))
    {
        updatePosition(updated_position);
        return true;
    }

    return false;
}

/**
 * Signature: bool checkMove(char)
 * Purpose: Determines if a provided move is possible for a ground enemy
 *          Utilizes 'N', 'E', 'S', 'W' for direction indication
 */
bool Ground::checkMove(char direction)
{
    pair<int, int> updated_position = position_;

    // Update the modified position dependent on the input direction
    switch (direction)
    {
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

    if ((updated_position.first >= 0) && (updated_position.first < current_map_->numColumns()))
    {
        if ((updated_position.second >= 0) && (updated_position.second < current_map_->numRows(updated_position.first)))
        {
            if (current_map_->tile(updated_position.first, updated_position.second).available())
            {
                return true;
            }
        }
    }

    return false;
}
