#include "Item.h"
#include "StatMod.h"
using namespace std;

Item::Item(string _name): name{_name} {}

string Item::getName(){
    return name;
}
void Item::updateName(string toAppend){
    name+=toAppend;
    return;
}
vector<StatMod *> &Item::getStatMod(){
    return statModifiers;
}
map<std::string,StatMod *> &Item::getModifiers(){
    return modifiers;
}