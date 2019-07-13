#include "ItemDescription.h"

using namespace std;

ItemDescription::~ItemDescription() {}

void ItemDescription::reload() {
    needsReload = true;
    return;
}

void ItemDescription::combineMods(map<string, StatMod>& modMap, const string& name,
                       const StatMod& statToAdd) {
    if (modMap.find(name) != modMap.end()) {
        modMap[name] = StatMod{modMap[name], statToAdd};
    } else {
        modMap[name] = statToAdd;
    }
}