#include "Consumable.h"
#include "BaseDescription.h"

using namespace std;

void Consumable::afterUse() { desc = make_shared<BaseDescription>(getName()); }

Consumable::Consumable(string name, shared_ptr<ItemDescription> active)
    : Item{name, active} {}
Consumable::~Consumable() {}