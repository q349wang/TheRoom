#ifndef RANGER_H_
#define RANGER_H_

#include "Player.h"

#include <vector>
#include <memory>
#include <utility>

/**
 * Class: Ranger - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Ranger : public Player {
 private:
    // Defines the ranger colour
   static const int colour = GameColours::DarkGreen;

 protected:
 public:
    // Constructor which requires health, energy, and attack information
    Ranger(double health, double energy, double attack, double armour, 
           std::pair<int,int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {}, 
           std::vector<std::shared_ptr<Equipable>> equipables = {});

    // Default destructor
    ~Ranger();

    // Utilize special movement to a specified position
    // Returns true if successful, and false otherwise
    bool useSpecial(std::pair<int, int>) override;

    // Provides a collection of coordinates that can be moved to under a special move
    std::vector<std::pair<int, int>> specialMoves() override;

   // Get colour of the player
    int getColour() override;
};

#endif