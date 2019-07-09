#include "Item.h"
#include "StatMod.h"
using namespace std;

Item::Item(string _name, StatMod *_StatMod): name{_name},StatMod{_StatMod} {}

std::string Item::getName(){
    return name;
}
void Item::updateName(string toAppend){
    name+=toAppend;
    return;
}
map<string,StatMod> getModifiers(){
    return modifiers;
}
