#include "Equipable.h"
#include "BaseDescription.h"

using namespace std;

map<string, StatMod> Equipable::getPassive() const { return passive; }

Equipable::Equipable(string name, shared_ptr<ItemDescription> active,
                     map<string, StatMod> passive, int durability)
    : Item{name, active}, passive{passive}, durability{durability} {}
Equipable::~Equipable() {}

// Decrement durability after use, (-1 is infinite)
void Equipable::afterUse()
{
    if (durability <= -1)
    {
        return;
    }
    else if (durability == 0)
    {
        desc = make_shared<BaseDescription>(getName());
    }
    else
    {
        durability--;
    }
}
