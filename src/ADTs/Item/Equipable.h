#ifndef _EQUIPABLE_H_
#define _EQUIPABLE_H_
#include "Item.h"
#include "ItemDescription.h"

/**
 * Class that represents equipable items
 * Do not break after 1 use
 * Also have passive stats which are not
 * affected by modifiers and are not
 * used with useItem
 */

class Equipable : public Item
{
    std::map<std::string, StatMod> passive;
    int durability;

public:
    std::map<std::string, StatMod> getPassive() const;
    Equipable(std::string name,
              std::shared_ptr<ItemDescription> desc,
              std::map<std::string, StatMod> passive, 
              int durability = -1);
    ~Equipable();
    
    void afterUse() override;
};

#endif