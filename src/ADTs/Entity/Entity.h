#ifndef ENTITY_H_
#define ENTITY_H_

#include "../Item/Consumable.h"
#include "../Item/Equipable.h"
#include "../../HelperClasses/GameConstants.h"
#include <vector>
#include <memory>
#include <utility>

class Map;

/**
 * Class: Entity - Abstract Base Class
 * Purpose: Entity maintains information specific to an entity within a game,
 *          including but not limited to health, energy, strength, current position,
 *          consumables, and equipables.
 */
class Entity
{
private:
protected:
  // Maintain a reference to the current map associated with the entity
  std::weak_ptr<Map> current_map_;

  // Maintain entity health, energy, armour, and attack information
  double health_;
  double energy_;
  double attackStrength_;
  double armour_;

  // Maintain entity name information
  std::string name_;

  // Maintain entity's current position
  std::pair<int, int> position_;

  // Maintain a collection of available consumables,
  // equipables, and equipped items
  std::vector<std::shared_ptr<Consumable>> consumables_;
  std::vector<std::shared_ptr<Equipable>> equipables_;

  // Maintain entity base health and energy amount
  // Note: Entity with health lower than this amount
  //       is considered to be inactive within the game
  //       Similarly, entities with energy lower than
  //       this amount cannot attack without regenerating
  static const double BASE_HEALTH_ENERGY;

  // Makes a specified move, without checking if valid
  void updatePosition(std::pair<int, int>);
public:
  // Constructor which requires health, energy, armour and attack information
  Entity(double health, double energy, double attack, double armour,
         std::string name, std::pair<int, int> position,
         std::vector<std::shared_ptr<Consumable>> consumables = {},
         std::vector<std::shared_ptr<Equipable>> equipables = {});

  // Delete the copy ctor to ensure appropriate use of class
  Entity(Entity &) = delete;

  // Pure virtual destructor to ensure Entity is an ABC
  virtual ~Entity() = 0;

  // Provides entity's current health, energy, attack, or position
  double getHealth();
  double getEnergy();
  double getAttack();
  double getArmour();
  std::pair<int, int> getPosition();

  // Inserts specfied equipable/consumable to current collection
  virtual void addEquipable(std::shared_ptr<Equipable>);
  void addConsumable(std::shared_ptr<Consumable>);

  // Provides a const reference to equipables/consumables
  std::vector<std::shared_ptr<Equipable>> &currentEquipables();
  std::vector<std::shared_ptr<Consumable>> &currentConsumables();

  // Perform an attack on a specified enemy
  double attack(std::shared_ptr<Entity>);

  // Check if a specified move is valid for the entity
  virtual bool checkMove(char) = 0;

  // Make a move in a specified direction (indicated using 'N', 'E', 'S', 'W')
  virtual bool makeMove(char) = 0;

  // Take damage or consume energy by a specified amount
  double takeDamage(double);
  void useEnergy(double);

  // Applies stat mod to a player
  void applyStat(std::string, StatMod);

  // Determine if an entity is dead or out of energy
  bool isDead();
  bool isOutOfEnergy();

  // Provides entity's name
  std::string getName();

  // Sets the map of a given player
  void setMap(std::shared_ptr<Map>);

  // Provides colour of entity displayed
  virtual int getColour() = 0;

  // Drops all items specified by a provided name
  bool dropItem(std::string);

  // Drops all enemy items onto current tile
  void dropAllItems();
};

#endif