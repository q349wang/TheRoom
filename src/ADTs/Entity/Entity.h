#ifndef ENTITY_H_
#define ENTITY_H_

#include<vector>
#include<memory>
#include<utility>

class Consumable;
class Equipable;
class Map;

/**
 * Class: Entity
 * Purpose: Declaration of the abstract base Entity.
 */
class Entity {
 private:
    Map* current_map_;
    
    double health_;
    double energy_;
    double attackStrength_;

    std::pair <int,int> position_;
    std::vector<Consumable*> consumables_;
    std::vector<Equipable*> equipables_;
    std::vector<Equipable*> equiped_;

    static const double BASE_HEALTH_ENERGY = 0.0; 

 protected:   
 public:
    Entity(){};
    virtual ~Entity()=0;

    double getHealth();
    double getEnergy();
    double getAttack();
    std::pair<int,int> getPosition();
    
    void addEquipable(Equipable&);
    void addConsumable(Consumable&);
    void equipEquipable(Equipable&);

    const std::vector<Equipable*>& currentEquipables();
    const std::vector<Consumable*>& currentConsumables();

    void attack(Entity*);
    bool checkMove(pair<int,int>);

    void takeDamage(double);
    void useEnergy(double);
    bool isDead();
    bool isOutOfEnergy();
};

#endif