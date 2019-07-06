#ifndef ENTITY_H_
#define ENTITY_H_

#include<vector>

class Consumable;
class Equipable;

/**
 * Class: Entity
 * Purpose: Declaration of the abstract base Entity.
 */
class Entity {
 private:
    double health_;
    double energy_;
    std::vector<Consumable> consumables_;
    std::vector<Equipable> equipables_;
    std::vector<Equipable> equiped_;
 protected:   
 public:
    Entity(){};
    virtual ~Entity()=0;

    double getHealth();
    double getEnergy();
    
    void addEquipable();
    void addConsumable();
    void equipEquipable();

    void takeDamage();
    void useEnergy();
    bool isDead();
};

#endif