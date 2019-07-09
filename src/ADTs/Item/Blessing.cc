#include "Blessing.h"
#include <string>
#include "StatMod.h"
using namespace std;

Blessing::Blessing(Item *_component): Modifier{_component} {
    component->updateName("Blessing");
    float a = 0;
    float b = 0;
    component->statModifiers.emplace_back(new StatMod(a,b));
};