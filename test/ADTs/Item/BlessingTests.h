#ifndef BLESSING_TESTS_H_
#define BLESSING_TESTS_H_

#include "../../TestsBase.h"
#include <map>
#include <string>

class StatMod;

class BlessingTests : public Tests {
    public:
    BlessingTests();
    ~BlessingTests();
    bool runTests() override;
    bool BlessingTestsBaseNoMods();
    bool BlessingTestsBaseMods();
    bool BlessingTestsBaseModsReload();
};

#endif