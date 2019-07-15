#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"
#include "Consumable.h"
#include "Equipable.h"
#include "Map.h"

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
    // Maintain player's special movement cooldown turn counter
    int cooldown_;

    // Maintain the base special cooldown and special ready amounts
    static const int BASE_SPECIAL_COOLDOWNN = 5;
    static const int BASE_SPECIAL_READY = 0 ;

    // Maintain all consumed items and relevant information
    std::vector<std::shared_ptr<Consumable>> consumed_;
 
 public:
    // Constructor which requires health, energy, and attack information
    Player(double health, double energy, double attack, 
           std::pair<int,int> position,
           std::vector<std::shared_ptr<Consumable>> consumables = {}, 
           std::vector<std::shared_ptr<Equipable>> equipables = {});
    // Pure virtual destructor to ensure Player is an ABC
    virtual ~Player() = 0;
    
    // Decrease cooldown after every specified turn
    void decreaseCooldown();

    // Reset cooldown after utilizing the special movement
    void resetCooldown();
    
    // Determines if special movement is ready to be used
    bool specialReady();

    // Checks if a provided move is possible for player
    bool checkMove(std::pair<int, int>) override;

    // Make a move in a specified direction (indicated using 'R', 'L', 'U' 'D')
    // Note: If move is successful, will return true, otherwise false
    bool makeMove(char) override;

    // Consume item, specified by the consumable name
    void consumeConsumable(std::string);
    
    // Utilize special movement to a specified position
    // Returns true if successful, and false otherwise
    virtual bool useSpecial(std::pair<int, int>) = 0;

    // Provides a vector of coordinates that can be moved to under a special move
    virtual std::vector<std::pair<int, int>> specialMoves() = 0;

    // Picks up all items from current tile and empties tile as well
    void pickUpItems();
};

/**
 * Class: Ranger - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Ranger : public Player {
 private:
 protected:
 public:
    // Constructor which requires health, energy, and attack information
    Ranger(double health, double energy, double attack, 
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
};

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

/**
 * Class: Warrior - Derived Class
 * Purpose: Player maintains information specific to an player within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, equipables, and special move information;
 */
class Warrior : public Player {
 private:
 protected:
 public:

    // Constructor which requires health, energy, and attack information
    Warrior(double health, double energy, double attack, 
            std::pair<int,int> position,
            std::vector<std::shared_ptr<Consumable>> consumables = {}, 
            std::vector<std::shared_ptr<Equipable>> equipables = {});

    // Default destructor
    ~Warrior();

    // Utilize special movement to a specified position
    // Returns true if successful, and false otherwise
    bool useSpecial(std::pair<int, int>) override;

    // Provides a collection of coordinates that can be moved to under a special move
    std::vector<std::pair<int, int>> specialMoves() override;
};

#endif