#ifndef _ITEM_H_
#define _ITEM_H_
#include <string>
#include <StatMod.h>
#include <map>

class Item{
    std::string name;
    StatMod *StatMod;
    vector<StatMod *> statModifiers;
    std::map<std::string,StatMod> modifiers;
    public:
        Item(std::string _name, StatMod *_StatMod);
        std::map<std::string,StatMod> getModifiers();
        std::string getName;
        void updateName(string toAppend);
        std::map<std::string,StatMod> useItem();
}

#endif