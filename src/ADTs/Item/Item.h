#ifndef _ITEM_H_
#define _ITEM_H_
#include <string>
#include "StatMod.h"
#include <map>
#include <vector>

class Item{
    std::string name;
    std::map<std::string,StatMod *> modifiers;
    vector<StatMod *> statModifiers;
    public:
        vector<StatMod *> &getStatMod();
        Item(std::string _name);
        std::map<std::string,StatMod *> &getModifiers();
        std::string getName();
        void updateName(std::string toAppend);
        virtual std::map<std::string,StatMod> useItem();
        virtual ~Item();
};

#endif