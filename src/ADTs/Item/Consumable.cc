#include "Consumable.h"

using namespace std;

void Consumable::afterUse() { desc = make_shared<ItemDescription>(getName()); }

Consumable::Consumable(string name, shared_ptr<ItemDescription> active)
    : Item{name, active} {}
Consumable::~Consumable() {}