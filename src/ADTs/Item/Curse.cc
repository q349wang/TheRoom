#include "Curse.h"
#include <string>
using namespace std;

Curse::Curse(string name, StatMod stat, shared_ptr<ItemDescription> item)
    : Modifier{item}, name{name}, stat{stat} {}
Curse::~Curse() {}
string Curse::getName() const { return "Cursed " + name + " " + component->getName(); }
map<string, StatMod>& Curse::getModifiers() {
    map<string, StatMod>& modMap = component->getModifiers();
    // If reloading the modifier list, combine the modificatons with the base modifiers
    if (needsReload) {
        // Since curse modifiers are a debuff, need to apply them to the modifier list accordingly
        combineMods(modMap, name, StatMod{-stat.getAdder(), 1.0/stat.getMultiplier()});
    }
    return modMap;
}