#ifndef FLYING_H_
#define FLYING_H_

#include "Enemy.h"

#include <memory>
#include <vector>
#include <utility>

/**
 * Class: Flying - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Flying : public Enemy
{
private:
protected:
public:
    // Constructor which requires health, energy, armour, and attack information
    Flying(double health, double energy, double attack, double armour,
           std::pair<int, int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {},
           std::vector<std::shared_ptr<Equipable>> equipables = {});

    // Defualt destructor
    ~Flying();

    // Make a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
    bool makeMove(char) override;

    // Check if a specified move is valid for the entity
    bool checkMove(char) override;

    // Provides name of flying enemy
    std::string getName() override;
};

#endif
