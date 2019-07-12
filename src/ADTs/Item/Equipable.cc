#include "Equipable.h"

using namespace std;

map<string, StatMod> Equipable::getPassive() { return passive->getModifiers(); }

Equipable::Equipable(string name, shared_ptr<ItemDescription> active,
                     shared_ptr<ItemDescription> passive)
    : Item{name, active}, passive{passive} {}
Equipable::~Equipable() {}
