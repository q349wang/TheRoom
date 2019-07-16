#ifndef ENTITY_H_
#define ENTITY_H_

#include "Consumable.h"
#include "Equipable.h"
#include "Map.h"

#include <vector>
#include <memory>
#include <utility>

/**
 * Class: Entity - Abstract Base Class
 * Purpose: Entity maintains information specific to an entity within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, and equipables.
 */
class Entity {
 private:
  // Maintain entity name
  static const std::string ENTITY_NAME;

 protected:
  // Applies specified modification to the current entity
  void applyModifications(std::pair<std::string, StatMod>&);

  // Maintain a reference to the current map associated with the entity
  std::shared_ptr<Map> current_map_;

  // Maintain entity health, energy, armour, and attack information
  double health_;
  double energy_;
  double attackStrength_;
  double armour_;

  // Maintain entity's current position
  std::pair<int,int> position_;

  // Maintain a collection of available consumables, 
  // equipables, and equiped items
  std::vector<std::shared_ptr<Consumable>> consumables_;
  std::vector<std::shared_ptr<Equipable>> equipables_;

  // Maintain all equiped items and relevant information
  std::vector<std::shared_ptr<Equipable>> equipabled_;

  // Maintain entity base health and energy amount
  // Note: Entity with health lower than this amount
  //       is considered to be inactive within the game
  //       Similarly, entities with energy lower than
  //       this amount cannot attack without regenerating
  static const double BASE_HEALTH_ENERGY = 0.0; 

  // Makes a specified move, without checking if valid
  void updatePosition(std::pair<int, int>);
   
 public:
  // Constructor which requires health, energy, armour and attack information
  Entity(double health, double energy, double attack, double armour,
         std::pair<int,int> position,
         std::vector<std::shared_ptr<Consumable>> consumables = {}, 
         std::vector<std::shared_ptr<Equipable>> equipables = {});

  // Delete the copy ctor to ensure appropriate use of class
  Entity(Entity&) = delete;

  // Pure virtual destructor to ensure Entity is an ABC
  virtual ~Entity() = 0;

  // Provides entity's current health, energy, attack, or position
  double getHealth();
  double getEnergy();
  double getAttack();
  double getArmour();
  std::pair<int,int> getPosition();
  
  // Inserts specfied equipable/consumable to current collection
  void addEquipable(std::shared_ptr<Equipable>);
  void addConsumable(std::shared_ptr<Consumable>);

  // Equiping item, specified by the equipable name
  void equipEquipable(std::string);

  // Provides a const reference to equipables/consumables
  const std::vector<std::shared_ptr<Equipable>>& currentEquipables();
  const std::vector<std::shared_ptr<Consumable>>& currentConsumables();

  // Perform an attack on a specified enemy
  double attack(std::shared_ptr<Entity>);
  
  // Check if a specified move is valid for the entity
  virtual bool checkMove(char) = 0;

  // Make a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
  virtual bool makeMove(char) = 0;

  // Take damage or consume energy by a specified amount
  double takeDamage(double);
  void useEnergy(double);

  // Determine if an entity is dead or out of energy
  bool isDead();
  bool isOutOfEnergy();

  // Provides entity's name
  std::string getName();
};

#endif