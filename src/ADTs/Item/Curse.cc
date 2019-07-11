#include "Curse.h"
#include <string>
using namespace std;

Curse::Curse(Item * name,float _adder, float _multiplier): Modifier{name} {
    component->updateName("Curse");
    StatMod* toInsert = new StatMod(_adder,_multiplier);
    component->getStatMod().emplace_back(toInsert);
    component->getModifiers().insert({"Curse",toInsert});
}