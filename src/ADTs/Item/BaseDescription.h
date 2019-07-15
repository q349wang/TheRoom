#ifndef BASE_DESCRIPTION_H_
#define BASE_DESCRIPTION_H_

#include <string>
#include "ItemDescription.h"

class BaseDescription : public ItemDescription {
    std::string name;

    std::map<std::string, StatMod> modifierList;

   public:
    BaseDescription(std::string);
    BaseDescription(std::string, std::map<std::string, StatMod>);
    ~BaseDescription();

    std::map<std::string, StatMod> &getModifiers() override;
    std::string getName() override;
};

#endif