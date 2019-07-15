#ifndef ENEMY_H_
#define ENEMY_H_

#include "Entity.h"
#include "Consumable.h"
#include "Equipable.h"

#include <memory>
#include <vector>
#include <utility>

/**
 * Class: Enemy - Abstract Base Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, and equipables;
 */
class Enemy : public Entity {
 private:
 protected:
 public:
    // Constructor which requires health, energy, and attack information
    Enemy(double health, double energy, double attack, 
           std::pair<int,int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {}, 
           std::vector<std::shared_ptr<Equipable>> equipables = {});

    // Pure virtual destructor to ensure Player is an ABC
    virtual ~Enemy() = 0;

    // Make a move in a specified direction (indicated using 'R', 'L', 'U', 'D')
    virtual bool makeMove(char) = 0;

    // Drops all enemy items onto current tile
    void dropAllItems();
};

/**
 * Class: Flying - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Flying : public Enemy {
 private:
 protected:
 public:
     // Constructor which requires health, energy, and attack information
    Flying(double health, double energy, double attack, 
           std::pair<int,int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {}, 
           std::vector<std::shared_ptr<Equipable>> equipables = {});

    // Defualt destructor
    ~Flying();

    // Make a move in a specified direction (indicated using 'R', 'L', 'U', 'D')
    bool makeMove(char) override;
};

/**
 * Class: Ground - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Ground : public Enemy {
 private:
 protected:
 public:
     // Constructor which requires health, energy, and attack information
    Ground(double health, double energy, double attack, 
           std::pair<int,int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {}, 
           std::vector<std::shared_ptr<Equipable>> equipables = {});
    
    // Defualt destructor
    ~Ground();

    // Make a move in a specified direction (indicated using 'R', 'L', 'U', 'D')
    bool makeMove(char) override;
};

#endif