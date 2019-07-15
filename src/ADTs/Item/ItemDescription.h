#ifndef _ITEM_DESCRIPTION_H_
#define _ITEM_DESCRIPTION_H_
#include <map>
#include <string>
#include <vector>
#include "StatMod.h"

/**
 * Stores the description of an item
 * using a decorator design pattern.
 */
class ItemDescription
{
protected:
    bool needsReload = true;

public:
    static void combineMods(std::map<std::string, StatMod> &, const std::string &,
                     const StatMod &);
    virtual std::map<std::string, StatMod> &getModifiers() = 0;
    virtual void reload();
    virtual std::string getName() const = 0;
    virtual ~ItemDescription() = 0;
};

#endif