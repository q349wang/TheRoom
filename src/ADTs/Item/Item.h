#ifndef _ITEM_H_
#define _ITEM_H_
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "StatMod.h"

class ItemDescription;

/**
 * Contains the description of an item
 * and the behaviour of the item when used
 */
class Item {
    std::string name;

    virtual void afterUse();

   protected:
    std::shared_ptr<ItemDescription> desc;

   public:
    virtual std::map<std::string, StatMod> &getModifiers();
    virtual std::string getName() const;
    std::map<std::string, StatMod> useItem(std::string);
    Item(std::string, std::shared_ptr<ItemDescription>);
    virtual ~Item() = 0;
};

#endif