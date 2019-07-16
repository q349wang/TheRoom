#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"

#include <vector>
#include <memory>
#include <utility>

/**
 * Class: Player - Abstract Base Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, and equipables;
 */
class Player: public Entity {
 private:
 protected:
    // Maintain all equiped items and relevant information
    std::vector<std::shared_ptr<Equipable>> equiped_;

    // Maintain all consumed items and relevant information
    std::vector<std::shared_ptr<Consumable>> consumed_;

    // Maintain player's special movement cooldown turn counter
    int cooldown_;

    // Maintain the base special cooldown and special ready amounts
    static const int BASE_SPECIAL_COOLDOWNN = 5;
    static const int BASE_SPECIAL_READY = 0 ;
 
 public:
    // Constructor which requires health, energy, armour, and attack information
    Player(double health, double energy, double attack, double armour,
           std::pair<int,int> position, std::string name,
           std::vector<std::shared_ptr<Consumable>> consumables = {}, 
           std::vector<std::shared_ptr<Equipable>> equipables = {});

    // Pure virtual destructor to ensure Player is an ABC
    virtual ~Player() = 0;
    
    // Decrease cooldown after every specified turn
    void decreaseCooldown();

    // Reset cooldown after utilizing the special movement
    void resetCooldown();

    // Provides the current cooldown on the special movement
    int getCooldown();
    
    // Determines if special movement is ready to be used
    bool specialReady();

    // Checks if a provided move is possible for player
    bool checkMove(char) override;

    // Make a move in a specified direction (indicated using 'R', 'L', 'U' 'D')
    // Note: If move is successful, will return true, otherwise false
    bool makeMove(char) override;

    // Equips an equipable and also activates all passive stat mods
    void addEquipable(std::shared_ptr<Equipable>) override;

    // Consume item, specified by the consumable name
    void consumeConsumable(std::string);

    // Equip item, specified by equipable name
    void equipEquipable(std::string);
    
    // Utilize special movement to a specified position
    // Returns true if successful, and false otherwise
    virtual bool useSpecial(std::pair<int, int>) = 0;

    // Provides a vector of coordinates that can be moved to under a special move
    virtual std::vector<std::pair<int, int>> specialMoves() = 0;

    // Picks up all items from current tile and empties tile as well
    void pickUpItems(); 
};

#endif