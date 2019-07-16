#include "Item.h"
#include "ItemDescription.h"

using namespace std;

string Item::getName() const { return desc->getName(); }

map<string, StatMod>& Item::getModifiers() {
    return desc->getModifiers();
}

void Item::afterUse() {}

map<string, StatMod> Item::useItem() {
    map<string, StatMod> itemMods{getModifiers()};

    afterUse();
    return itemMods;
}

Item::Item(string name, shared_ptr<ItemDescription> desc)
    : name{name}, desc{desc} {}
Item::~Item() {}
