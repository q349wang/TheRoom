#ifndef _ITEM_H_
#define _ITEM_H_
#include <string>
#include <StatMod.h>
#include <map>

class Item{
    std::string name;
    StatMod *StatMod;
    std::map<std::string,StatMod> modifiers;
    vector<StatMod *> statModifiers;
    public:
        Item(std::string _name, StatMod *_StatMod);
        std::map<std::string,StatMod> getModifiers();
        std::string getName;
        void updateName(std::string toAppend);
        std::map<std::string,StatMod> useItem();
}

#endif