#include "Blessing.h"
#include <string>
using namespace std;

Blessing::Blessing(string name, StatMod stat, shared_ptr<ItemDescription> item)
    : Modifier{item}, name{name}, stat{stat} {}
Blessing::~Blessing() {}

string Blessing::getName() { return "Blessed " + name + " " + component->getName(); }
map<string, StatMod>& Blessing::getModifiers() {
    map<string, StatMod>& modMap = component->getModifiers();
    if (needsReload) {
        combineMods(modMap, name, stat);
    }
    return modMap;
}