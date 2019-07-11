#include "Blessing.h"
#include <string>
#include "StatMod.h"
using namespace std;

Blessing::Blessing(string name): Modifier{name} {
    component->updateName("Blessing");
    float a = 0;
    float b = 0;
    StatMod* toInsert = new StatMod(a,b);
    component->getStatMod().emplace_back(toInsert);
    component->getModifiers().insert({"Blessing",toInsert});
};