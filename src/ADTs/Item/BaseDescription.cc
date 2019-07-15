#include "BaseDescription.h"
using namespace std;

BaseDescription::BaseDescription(string name) : name{name} {}
BaseDescription::BaseDescription(string name, map<string, StatMod> modList) : name{name}, baseInfo{modList} {}
BaseDescription::~BaseDescription() {}
map<std::string, StatMod> &BaseDescription::getModifiers() {
	// If cached modifier list needs to be updated, reset it
	if (needsReload) {
		modifierList.clear();
		modifierList = baseInfo;
		needsReload = false;
	}
    return modifierList;
}
string BaseDescription::getName() const { return name; }
