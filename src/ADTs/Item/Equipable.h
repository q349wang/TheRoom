#ifndef _EQUIPABLE_H_
#define _EQUIPABLE_H_
#include <string>
#include "StatMod.h"
#include "Item.h"

class Equipable: public Item {
    public:
       // std::map<std::string,StatMod> getPassive();
        Equipable(std::string);
        ~Equipable();

};

#endif