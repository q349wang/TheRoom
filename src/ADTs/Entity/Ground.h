#ifndef GROUND_H_
#define GROUND_H_

#include "Entity.h"
#include "Consumable.h"
#include "Equipable.h"

#include <memory>
#include <vector>
#include <utility>

/**
 * Class: Ground - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Ground : public Enemy {
 private:
   // Maintain entity name
  static const std::string ENTITY_NAME;

 protected:
 public:
     // Constructor which requires health, energy, armour, and attack information
    Ground(double health, double energy, double attack, double armour, 
           std::pair<int,int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {}, 
           std::vector<std::shared_ptr<Equipable>> equipables = {});
    
    // Defualt destructor
    ~Ground();

    // Make a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
    bool makeMove(char) override;

    // Provides name of the ground enemy
    std::string getName() override;

    // Checks if a provided move is possible for ground enemy
    bool checkMove(char) override;
};

#endif
