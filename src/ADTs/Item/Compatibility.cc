#include "Compatibility.h"
#include <string>
using namespace std;

Compatability::Compatability(string heroClass, StatMod stat, shared_ptr<ItemDescription> item)
    : heroClass{heroClass}, stat{stat}, Modifier{item} {}

Compatability::~Compatability(){}

string Compatability::getName() { return component->getName() + " for " + heroClass; }
map<string, StatMod>& Compatability::getModifiers() {
    map<string, StatMod>& modMap = component->getModifiers();
    if (needsReload) {
        combineMods(modMap, heroClass, stat);
    }
    return modMap;
}