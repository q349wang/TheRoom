#include "Consumable.h"
#include "BaseDescription.h"

using namespace std;

// After using a consumable item all stats are deleted
void Consumable::afterUse() { desc = make_shared<BaseDescription>(getName()); }

Consumable::Consumable(string name, shared_ptr<ItemDescription> active)
    : Item{name, active} {}
Consumable::~Consumable() {}
