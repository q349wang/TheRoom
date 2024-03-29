#include "Compatibility.h"
#include <string>
using namespace std;

Compatability::Compatability(string heroClass, StatMod stat, shared_ptr<ItemDescription> item)
    : Modifier{item}, heroClass{heroClass}, stat{stat} {}

Compatability::~Compatability() {}

string Compatability::getName() const { return component->getName() + " for " + heroClass; }
map<string, StatMod> &Compatability::getModifiers()
{
    map<string, StatMod> &modMap = component->getModifiers();
    // If reloading the modifier list, combine the modificatons with the base modifiers
    if (needsReload)
    {
        combineMods(modMap, heroClass, stat);
    }
    return modMap;
}
