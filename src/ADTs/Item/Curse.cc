#include "Curse.h"
#include <string>
using namespace std;

Curse::Curse(string name, StatMod stat, shared_ptr<ItemDescription> item)
    : name{name}, stat{stat}, Modifier{item} {}

string Curse::getName() { return "Cursed " + name + " " + component->getName(); }
map<string, StatMod>& Curse::getModifiers() {
    map<string, StatMod>& modMap = component->getModifiers();
    if (needsReload) {
        combineMods(modMap, name, StatMod{-stat.getAdder, 1.0 / stat.getMultiplier});
    }
    return modMap;
}