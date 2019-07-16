#ifndef BASE_DESCRIPTION_H_
#define BASE_DESCRIPTION_H_

#include <string>
#include "ItemDescription.h"

/*
    Class used as base case for decorator
    pattern. Stores the name of the item
    as well as the modifiers and base stats
    of the item
 */
class BaseDescription : public ItemDescription {
    std::string name;

    std::map<std::string, StatMod> baseInfo;
    std::map<std::string, StatMod> modifierList;

   public:
    BaseDescription(std::string);
    BaseDescription(std::string, std::map<std::string, StatMod>);
    ~BaseDescription();

    std::map<std::string, StatMod> &getModifiers() override;
    std::string getName() const override;
};

#endif
