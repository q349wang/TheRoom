#ifndef _CONSUMABLE_H_
#define _CONSUMABLE_H_
#include <string>
#include "Item.h"

class Consumable: public Item {
    Consumable(std::string);
    ~Consumable();
};

#endif