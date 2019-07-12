#include "Equipable.h"

using namespace std;

map<string, StatMod> Equipable::getPassive() { return passive; }

Equipable::Equipable(string name, shared_ptr<ItemDescription> active,
                     map<string, StatMod>  passive)
    : Item{name, active}, passive{passive} {}
Equipable::~Equipable() {}
