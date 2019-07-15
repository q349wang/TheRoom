#ifndef _CONSUMABLE_H_
#define _CONSUMABLE_H_
#include "ItemDescription.h"
#include "Item.h"

/**
 * Represents a consumable item
 * Consumable items are useless after one use
 */
class Consumable: public Item {
    public:
        Consumable(std::string, std::shared_ptr<ItemDescription>);
        void afterUse() override;
        ~Consumable();
};

#endif