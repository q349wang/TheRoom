#include "BaseDescription.h"
using namespace std;

BaseDescription::BaseDescription(string name) : name{name} {}
BaseDescription::BaseDescription(string name, map<string, StatMod> modList) : name{name}, modifierList{modList} {}
BaseDescription::~BaseDescription() {}
map<std::string, StatMod> &BaseDescription::getModifiers() {
	if (needsReload) {
		modifierList.clear();
		needsReload = false;
	}
    return modifierList;
}
string BaseDescription::getName() { return name; }