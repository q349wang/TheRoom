#ifndef MAGE_H_
#define MAGE_H_

#include "Entity.h"
#include "Consumable.h"
#include "Equipable.h"
#include "Map.h"
#include "Player.h"

#include <vector>
#include <memory>
#include <utility>

/**
 * Class: Mage - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Mage : public Player {
 private:
 protected:
    int teleport_amount_;
 public:
    // Constructor which requires health, energy, and attack information
    Mage(int teleport, double health, double energy, double attack, 
         std::pair<int,int> position,
         std::vector<std::shared_ptr<Consumable>> consumables = {}, 
         std::vector<std::shared_ptr<Equipable>> equipables = {});
    
    // Default destructor
    ~Mage();

    // Utilize special movement to a specified position
    // Returns true if successful, and false otherwise
    bool useSpecial(std::pair<int, int>) override;

    // Provides a collection of coordinates that can be moved to under a special move
    std::vector<std::pair<int, int>> specialMoves() override;
};

#endif