#ifndef _MODIFIER_H_
#define _MODIFIER_H_
#include <memory>
#include "ItemDescription.h"
#include "StatMod.h"

/**
 * Abstract class for decorator modifiers
 * to inherit from
 */
class Modifier : public ItemDescription {
   protected:
    std::shared_ptr<ItemDescription> component;

   public:
    Modifier(std::shared_ptr<ItemDescription>);
    virtual ~Modifier() = 0;
    std::map<std::string, StatMod> &getModifiers() override;
    std::string getName() const override;
    void reload() override;
};

#endif