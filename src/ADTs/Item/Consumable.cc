#include "Consumable.h"
#include "BaseDescription.h"

using namespace std;

// After use, clear the stats of a consumable
void Consumable::afterUse() { desc = make_shared<BaseDescription>(getName()); }

Consumable::Consumable(string name, shared_ptr<ItemDescription> active)
    : Item{name, active} {}
Consumable::~Consumable() {}