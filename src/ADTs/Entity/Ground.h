#ifndef GROUND_H_
#define GROUND_H_

#include "Enemy.h"

#include <memory>
#include <vector>
#include <utility>

/**
 * Class: Ground - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Ground : public Enemy
{
private:
protected:
public:
    // Constructor which requires health, energy, armour, and attack information
    Ground(double health, double energy, double attack, double armour,
           std::pair<int, int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {},
           std::vector<std::shared_ptr<Equipable>> equipables = {});

    // Defualt destructor
    ~Ground();

    // Make a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
    bool makeMove(char) override;

    // Check if a specified move is valid for the entity
    bool checkMove(char) override;
};

#endif
