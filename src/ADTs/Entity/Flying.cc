#include "Flying.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

#include <memory>
#include <vector>
#include <utility>

using namespace std;

/**
 * Signature: Ranger(double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial flying enemy's health, energy, and position
 */
Flying::Flying(double health, double energy, double attack, double armour, pair<int, int> position,
               vector<shared_ptr<Consumable>> consumables,
               vector<shared_ptr<Equipable>> equipables) : 
               Enemy{health, energy, attack, armour, "Flying", position, consumables, equipables} {}

/**
 * Signature: ~Entity()
 * Purpose: Defualt Destructor
 */
Flying::~Flying() {}

/**
 * Signature: bool makeMove(char)
 * Purpose: Makes a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
 *          If the move was valid, returns true, otherwise remains startionary and returns false
 */
bool Flying::makeMove(char direction)
{
    int right = 1, left = 1, up = 1, down = 1;

    switch (direction) {
        case 'E':

            // Determine the first wall or non-existent tile from the
            // current position in the right direction
            if ((position_.first + right) < current_map_->numColumns(position_.second))
            {
                while (!(current_map_->tile((position_.first + right), position_.second).available()))
                {
                    if ((position_.first + right) < (current_map_->numColumns(position_.second) - 1))
                    {
                        right++;
                    }
                    else
                    {
                        right++;
                        break;
                    }
                }
            }

            // Insert the furthest available tile from the current tile position after an
            // immediate contigous block of wall tiles in the right direction
            if (((position_.first + right) < current_map_->numColumns(position_.second)) &&
                (current_map_->tile((position_.first + right), position_.second).available())) {
                updatePosition({(position_.first + right), position_.second});
                return true;
            }
            else {
                return false;
            }

        case 'W':

            // Determine the first wall or non-existent tile from the
            // current position in the left direction
            if ((position_.first - left) >= 0) {
                while (current_map_->tile((position_.first - left), position_.second).available())
                {
                    if ((position_.first - left) > 0) {
                        left++;
                    }
                    else {
                        left++;
                        break;
                    }
                }
            }

            // Insert the furthest available tile from the current tile position after an
            // immediate contigous block of wall tiles in the left direction
            if (((position_.first - left) >= 0) &&
                (current_map_->tile((position_.first - left), position_.second).available()))
            {
                updatePosition({(position_.first - left), position_.second});
                return true;
            }
            else
            {
                return false;
            }

        case 'N':

            // Determine the first wall or non-existent tile from the
            // current position in the up direction
            if ((position_.second + up) < (current_map_->numRows()))
            {
                while (current_map_->tile(position_.first, (position_.second + up)).available())
                {
                    if ((position_.second + up) < (current_map_->numRows() - 1))
                    {
                        up++;
                    }
                    else
                    {
                        up++;
                        break;
                    }
                }
            }

            // Insert the furthest available tile from the current tile position after an
            // immediate contigous block of wall tiles in the up direction
            if (((position_.second + up) < current_map_->numRows()) &&
                (current_map_->tile(position_.first, (position_.second + up)).available()))
            {
                updatePosition({position_.first, (position_.second + up)});
                return true;
            }
            else
            {
                return false;
            }

        case 'S':
            // Determine the first wall or non-existent tile from the
            // current position in the up direction
            if ((position_.second - down) >= 0)
            {
                while (current_map_->tile(position_.first, (position_.second - down)).available())
                {
                    if ((position_.second - down) > 0)
                    {
                        down++;
                    }
                    else
                    {
                        down++;
                        break;
                    }
                }
            }

            // Insert the furthest available tile from the current tile position after an
            // immediate contigous block of wall tiles in the down direction
            if (((position_.second - down) >= 0) &&
                (current_map_->tile(position_.first, (position_.second - down)).available()))
            {
                updatePosition({position_.first, (position_.second - down)});
                return true;
            }
            else
            {
                return false;
            }

        default:
            // Return false if any other input is detected
            return false;
    }
}

/**
 * Signature: bool checkMove(char)
 * Purpose: Checks if a specified move in a given direction is valid
 */
bool Flying::checkMove(char direction)
{
    int right = 1, left = 1, up = 1, down = 1;

    switch (direction)
    {
    case 'E':

        // Determine the first wall or non-existent tile from the
        // current position in the right direction
        if ((position_.first + right) < current_map_->numColumns(position_.second))
        {
            while (!(current_map_->tile((position_.first + right), position_.second).available()))
            {
                if ((position_.first + right) < (current_map_->numColumns(position_.second) - 1))
                {
                    right++;
                }
                else
                {
                    right++;
                    break;
                }
            }
        }

        // Insert the furthest available tile from the current tile position after an
        // immediate contigous block of wall tiles in the right direction
        if (((position_.first + right) < current_map_->numColumns(position_.second)) &&
            (current_map_->tile((position_.first + right), position_.second).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

    case 'W':

        // Determine the first wall or non-existent tile from the
        // current position in the left direction
        if ((position_.first - left) >= 0)
        {
            while (current_map_->tile((position_.first - left), position_.second).available())
            {
                if ((position_.first - left) > 0)
                {
                    left++;
                }
                else
                {
                    left++;
                    break;
                }
            }
        }

        // Insert the furthest available tile from the current tile position after an
        // immediate contigous block of wall tiles in the left direction
        if (((position_.first - left) >= 0) &&
            (current_map_->tile((position_.first - left), position_.second).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

    case 'N':

        // Determine the first wall or non-existent tile from the
        // current position in the up direction
        if ((position_.second + up) < (current_map_->numRows()))
        {
            while (current_map_->tile(position_.first, (position_.second + up)).available())
            {
                if ((position_.second + up) < (current_map_->numRows() - 1))
                {
                    up++;
                }
                else
                {
                    up++;
                    break;
                }
            }
        }

        // Insert the furthest available tile from the current tile position after an
        // immediate contigous block of wall tiles in the up direction
        if (((position_.second + up) < current_map_->numRows()) &&
            (current_map_->tile(position_.first, (position_.second + up)).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

    case 'S':
        // Determine the first wall or non-existent tile from the
        // current position in the up direction
        if ((position_.second - down) >= 0)
        {
            while (current_map_->tile(position_.first, (position_.second - down)).available())
            {
                if ((position_.second - down) > 0)
                {
                    down++;
                }
                else
                {
                    down++;
                    break;
                }
            }
        }

        // Insert the furthest available tile from the current tile position after an
        // immediate contigous block of wall tiles in the down direction
        if (((position_.second - down) >= 0) &&
            (current_map_->tile(position_.first, (position_.second - down)).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

    default:
        // Return false if any other input is detected
        return false;
    }
}