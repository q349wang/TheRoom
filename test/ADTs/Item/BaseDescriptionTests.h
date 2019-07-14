#ifndef BASE_DESCRIPTION_TESTS_H_
#define BASE_DESCRIPTION_TESTS_H_

#include "../../TestsBase.h"
#include <map>
#include <string>

class StatMod;

class BaseDescriptionTests : public Tests {
    public:
    BaseDescriptionTests();
    ~BaseDescriptionTests();
    bool runTests() override;
    bool BaseDescriptionNoMods();
    bool BaseDescriptionWithMods();
    bool BaseDescriptionWithModsReload();
};

#endif