#include "Item.h"
#include "StatMod.h"
using namespace std;

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
void Item::setString(string input){
    name = input;
}
Item::~Item(){
    for(int i=0;i<statModifiers.size();i++){
        delete statModifiers[i];
    }
    statModifiers.clear();
}