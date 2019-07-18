#include "Mage.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

/**
 * Signature: Mage(double, double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial mage's health, energy, and position
 */
Mage::Mage(double health, double energy, double attack, double armour, pair<int, int> position,
           vector<shared_ptr<Consumable>> consumables,
           vector<shared_ptr<Equipable>> equipables) : Player{health, energy, attack, armour, "Mage", position, consumables, equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Defualt Destructor
 */
Mage::~Mage() {}

/**
 * Signature: bool useSpecial(pair<int, int>)
 * Purpose: Utilizes special move to specified location if possible
 * Note: Returns false if special move was unsuccessful, and true otherwise
 */
bool Mage::useSpecial(pair<int, int> location)
{
    if (auto mp = current_map_.lock())
    {
        if ((((abs(location.first - position_.first) <= TELEPORT_DISTANCE) &&
              ((location.second - position_.second) == 0)) ||
             ((abs(location.second - position_.second) <= TELEPORT_DISTANCE) &&
              ((location.first - position_.first) == 0))) &&
            (mp->tile(location.first, location.second).available()) &&
            (this->specialReady()))
        {
            position_ = location;
            return true;
        }
    }

    return false;
}

/**
 * Signature: vector<pair<int, int>> specialMoves()
 * Purpose: Provides a collection of coordinates that can be moved to under a special move
 * Note: This is an expensive operation, taking O(max{Row, Column}) time
 */
vector<pair<int, int>> Mage::specialMoves()
{

    vector<pair<int, int>> special_moves = {};
    if (auto mp = current_map_.lock())
    {
        for (int teleport = 1; teleport <= TELEPORT_DISTANCE; teleport++)
        {

            // Determine if a teleport in the right direction is possible
            if (((position_.first + teleport) < mp->numColumns(position_.second)) &&
                (mp->tile((position_.first + teleport), position_.second).available()))
            {
                special_moves.emplace_back((position_.first + teleport), position_.second);
            }

            // Determine if a teleport in the left direction is possible
            if (((position_.first - teleport) >= 0) &&
                (mp->tile((position_.first - teleport), position_.second).available()))
            {
                special_moves.emplace_back((position_.first - teleport), position_.second);
            }

            // Determine if a teleport in the up direction is possible
            if (((position_.second + teleport) < mp->numRows()) &&
                (mp->tile(position_.first, (position_.second + teleport)).available()))
            {
                special_moves.emplace_back(position_.first, (position_.second + teleport));
            }

            // Determine if a teleport in the down direction is possible
            if (((position_.second - teleport) >= 0) &&
                (mp->tile(position_.first, (position_.second + teleport)).available()))
            {
                special_moves.emplace_back(position_.first, (position_.second - teleport));
            }
        }
    }
    return special_moves;
}

/**
 * Signature: int getColour()
 * Purpose: Provides the mage player colour
 */
int Mage::getColour()
{
    return colour;
}
