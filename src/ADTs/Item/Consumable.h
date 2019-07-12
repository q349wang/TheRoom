#ifndef _CONSUMABLE_H_
#define _CONSUMABLE_H_
#include "ItemDescription.h"
#include "Item.h"

class Consumable: public Item {
    public:
        Consumable(std::string, std::shared_ptr<ItemDescription>);
        void afterUse() override;
        ~Consumable();
};

#endif