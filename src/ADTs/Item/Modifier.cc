#include "Modifier.h"
#include "ItemDescription.h"

using namespace std;

Modifier::Modifier(shared_ptr<ItemDescription> item) : component{item} {}
Modifier::~Modifier() {}

string Modifier::getName() { return component->getName(); }
map<string, StatMod>& Modifier::getModifiers() {
    return component->getModifiers();
}

void Modifier::reload() {
    needsReload = true;
    component->reload();
	return;
}
