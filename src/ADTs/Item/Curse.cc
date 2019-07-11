#include "Curse.h"
#include <string>
using namespace std;

Curse::Curse(string name): Modifier{name} {
    component->updateName("Curse");
    float a;
    float b;
    StatMod* toInsert = new StatMod(a,b);
    component->getStatMod().emplace_back(toInsert);
    component->getModifiers().insert({"Blessing",toInsert});
}