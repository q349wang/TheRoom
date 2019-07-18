#include "Flying.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

#include <memory>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

/**
 * Signature: Ranger(double, double, double, pair<int, int>, 
 *                   vector<shared_ptr<Consumable>>, vector<shared_ptr<Equipable>>)
 * Purpose: Constructor which requires intial flying enemy's health, energy, and position
 */
Flying::Flying(double health,
               double energy,
               double attack,
               double armour,
               pair<int, int> position)
    : Enemy{health, energy, attack, armour, "Flying", position} {}

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
    if (auto mp = current_map_.lock())
    {

        cout << "flying" << endl;
        int right = 1, left = 1, up = 1, down = 1;

        switch (direction)
        {
        case 'E':
            cout << direction << endl;
            // Determine the first wall or non-existent tile from the
            // current position in the right direction
            if ((position_.first + right) < mp->numColumns(position_.second))
            {
                while (!(mp->tile((position_.first + right), position_.second).available()))
                {
                    if ((position_.first + right) < (mp->numColumns(position_.second) - 1))
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
            if (((position_.first + right) < mp->numColumns(position_.second)) &&
                (mp->tile((position_.first + right), position_.second).available()))
            {
                updatePosition({(position_.first + right), position_.second});
                return true;
            }
            else
            {
                return false;
            }

            break;

        case 'W':
            cout << direction << endl;
            // Determine the first wall or non-existent tile from the
            // current position in the left direction
            if ((position_.first - left) >= 0)
            {
                while (!mp->tile((position_.first - left), position_.second).available())
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
            cout << "updated pos: " << position_.first - left << " " << position_.second << endl;

            // Insert the furthest available tile from the current tile position after an
            // immediate contigous block of wall tiles in the left direction
            if (((position_.first - left) >= 0) &&
                (mp->tile((position_.first - left), position_.second).available()))
            {
                updatePosition({(position_.first - left), position_.second});
                return true;
            }
            else
            {
                return false;
            }

            break;

        case 'S':
            cout << direction << endl;
            // Determine the first wall or non-existent tile from the
            // current position in the down direction
            if ((position_.second + down) < (mp->numRows()))
            {
                while (!mp->tile(position_.first, (position_.second + down)).available())
                {
                    if ((position_.second + down) < (mp->numRows() - 1))
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
            if (((position_.second + down) < mp->numRows()) &&
                (mp->tile(position_.first, (position_.second + down)).available()))
            {
                updatePosition({position_.first, (position_.second + down)});
                return true;
            }
            else
            {
                return false;
            }

            break;

        case 'N':
            cout << direction << endl;
            // Determine the first wall or non-existent tile from the
            // current position in the up direction
            if ((position_.second - up) >= 0)
            {
                while (!mp->tile(position_.first, (position_.second - up)).available())
                {
                    if ((position_.second - up) > 0)
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
            if (((position_.second - up) >= 0) &&
                (mp->tile(position_.first, (position_.second - up)).available()))
            {
                updatePosition({position_.first, (position_.second - up)});
                return true;
            }
            else
            {
                return false;
            }

            break;

        default:
            // Return false if any other input is detected
            return false;
        }
    }
    return false;
}

/**
 * Signature: bool checkMove(char)
 * Purpose: Checks if a specified move in a given direction is valid
 */
bool Flying::checkMove(char direction)
{
    if (auto mp = current_map_.lock()) {
    int right = 1, left = 1, up = 1, down = 1;

    switch (direction)
    {
    case 'E':

        // Determine the first wall or non-existent tile from the
        // current position in the right direction
        if ((position_.first + right) < mp->numColumns(position_.second))
        {
            while (!(mp->tile((position_.first + right), position_.second).available()))
            {
                if ((position_.first + right) < (mp->numColumns(position_.second) - 1))
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
        if (((position_.first + right) < mp->numColumns(position_.second)) &&
            (mp->tile((position_.first + right), position_.second).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

        break;

    case 'W':

        // Determine the first wall or non-existent tile from the
        // current position in the left direction
        if ((position_.first - left) >= 0)
        {
            while (mp->tile((position_.first - left), position_.second).available())
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
            (mp->tile((position_.first - left), position_.second).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

        break;

    case 'S':

        // Determine the first wall or non-existent tile from the
        // current position in the down direction
        if ((position_.second + down) < (mp->numRows()))
        {
            while (mp->tile(position_.first, (position_.second + down)).available())
            {
                if ((position_.second + down) < (mp->numRows() - 1))
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
        if (((position_.second + down) < mp->numRows()) &&
            (mp->tile(position_.first, (position_.second + down)).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

        break;

    case 'N':
        // Determine the first wall or non-existent tile from the
        // current position in the up direction
        if ((position_.second - up) >= 0)
        {
            while (mp->tile(position_.first, (position_.second - up)).available())
            {
                if ((position_.second - up) > 0)
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
        if (((position_.second - up) >= 0) &&
            (mp->tile(position_.first, (position_.second - up)).available()))
        {
            return true;
        }
        else
        {
            return false;
        }

        break;

    default:
        // Return false if any other input is detected
        return false;
    }
    }
    return false;
}

/**
 * Signature: int getColour()
 * Purpose: Provides the flying enemy colour
 */
int Flying::getColour()
{
    return colour;
}
