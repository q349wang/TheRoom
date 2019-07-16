#include "BlessingTests.h"
#include "../../../src/ADTs/Item/Blessing.h"
#include "../../../src/ADTs/Item/BaseDescription.h"

#include <memory>

using namespace std;

BlessingTests::BlessingTests() {}
BlessingTests::~BlessingTests() {}
bool BlessingTests::runTests()
{
    bool noFail = true;

    // Base Description with no modifiers
    if (!BlessingTestsBaseNoMods())
    {
        cout << "Failed BlessingTestsBaseNoMods" << endl;
        noFail = false;
    }

    // Base description with modifiers
    if (!BlessingTestsBaseMods())
    {
        cout << "Failed BlessingTestsBaseMods" << endl;
        noFail = false;
    }

    // Base description with modifiers and reload
    if (!BlessingTestsBaseModsReload())
    {
        cout << "Failed BlessingTestsBaseModsReload" << endl;
        noFail = false;
    }

    return noFail;
}

bool BlessingTests::BlessingTestsBaseNoMods()
{
    Blessing bless = Blessing{"Attack", StatMod{2.1, 1.0}, make_shared<BaseDescription>("Base")};

    string expectedName = "Blessed Attack Base";
    map<string, StatMod> expectedMap = map<string, StatMod>{{"Attack", StatMod{2.1, 1}}};

    return compareMap(bless.getModifiers(), expectedMap) && expectedName == bless.getName();
}
bool BlessingTests::BlessingTestsBaseMods()
{
    Blessing bless = Blessing{"Attack", StatMod{2.1, 1.0},
                              make_shared<BaseDescription>("Base", map<string, StatMod>{{"Attack", StatMod{2.1, 1.5}}})};

    string expectedName = "Blessed Attack Base";
    map<string, StatMod> expectedMap = map<string, StatMod>{{"Attack", StatMod{4.2, 2.5}}};

    return compareMap(bless.getModifiers(), expectedMap) && expectedName == bless.getName();
}
bool BlessingTests::BlessingTestsBaseModsReload()
{
    Blessing bless = Blessing{"Attack", StatMod{2.1, 1.0}, make_shared<BaseDescription>("Base")};

    string expectedName = "Blessed Attack Base";
    map<string, StatMod> expectedMap = map<string, StatMod>{{"Attack", StatMod{2.1, 1}}};

    bool check = compareMap(bless.getModifiers(), expectedMap) && expectedName == bless.getName();
    bless.reload();
    bool checkreload = compareMap(bless.getModifiers(), expectedMap) && expectedName == bless.getName();
    return check && checkreload;
}