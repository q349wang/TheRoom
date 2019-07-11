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
        vector<StatMod *> &getStatMod();
        std::map<std::string,StatMod *> &getModifiers();
        std::string getName();
        void updateName(std::string);
       // virtual std::map<std::string,StatMod> useItem()=0;
        virtual ~Item();
        void setString(std::string);
};

#endif