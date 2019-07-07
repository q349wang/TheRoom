#ifndef ENTITY_H_
#define ENTITY_H_

#include<vector>
#include<memory>

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
    
    std::vector<Consumable*> consumables_;
    std::vector<Equipable*> equipables_;
    std::vector<Equipable*> equiped_;

    static const double DEAD_HEALTH = 0.0; 

 protected:   
 public:
    Entity(){};
    virtual ~Entity()=0;

    double getHealth();
    double getEnergy();
    
    void addEquipable(Equipable&);
    void addConsumable(Consumable&);
    void equipEquipable(Equipable&);

    const std::vector<Equipable*>& currentEquipables();
    const std::vector<Consumable*>& currentConsumables();

    void attack(Entity*);
    bool checkMove(std::vector<int>);

    void takeDamage(double);
    void useEnergy(double);
    bool isDead();
};

#endif