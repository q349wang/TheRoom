#include "TestsBase.h"
#include "../src/ADTs/Item/StatMod.h"

Tests::~Tests() {}

bool Tests::compareMap(std::map<std::string, StatMod> lhs, std::map<std::string, StatMod> rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (auto mapKey : lhs)
    {
        if (!(lhs[mapKey.first] == rhs[mapKey.first]))
            return false;
    }

    return true;
}
