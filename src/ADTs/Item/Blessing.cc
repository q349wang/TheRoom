#include "Blessing.h"
#include <string>
#include "StatMod.h"
using namespace std;

Blessing::Blessing(Item* name, float _adder, float _multiplier): Modifier{name} {
    component->updateName(" Blessing");
    StatMod* toInsert = new StatMod(_adder,_multiplier);
    component->getStatMod().emplace_back(toInsert);
    component->getModifiers().insert({"Blessing",toInsert});
};