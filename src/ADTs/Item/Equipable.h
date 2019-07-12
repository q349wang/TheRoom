#ifndef _EQUIPABLE_H_
#define _EQUIPABLE_H_
#include "Item.h"
#include "ItemDescription.h"

class Equipable : public Item {
    std::shared_ptr<ItemDescription> passive;

   public:
    std::map<std::string, StatMod> getPassive();
    Equipable(std::string, std::shared_ptr<ItemDescription>, std::shared_ptr<ItemDescription>);
    ~Equipable();
};

#endif