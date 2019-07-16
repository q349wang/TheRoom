#include "BaseDescriptionTests.h"
#include "../../../src/ADTs/Item/BaseDescription.h"

using namespace std;

BaseDescriptionTests::BaseDescriptionTests() {}
BaseDescriptionTests::~BaseDescriptionTests() {}

bool BaseDescriptionTests::runTests()
{
    bool noFail = true;

    // Base Description with no modifiers
    if (!BaseDescriptionNoMods())
    {
        cout << "Failed BaseDescriptionNoMods" << endl;
        noFail = false;
    }

    // Base description with modifiers
    if (!BaseDescriptionWithMods())
    {
        cout << "Failed BaseDescriptionWithMods" << endl;
        noFail = false;
    }

    // Base description with modifiers and reload
    if (!BaseDescriptionWithModsReload())
    {
        cout << "Failed BaseDescriptionWithModsReload" << endl;
        noFail = false;
    }

    return noFail;
}
bool BaseDescriptionTests::BaseDescriptionNoMods()
{
    BaseDescription base{"Name"};

    map<string, StatMod> expectedMods;

    if (base.getName() != "Name")
        return false;
    if (!compareMap(base.getModifiers(), expectedMods))
        return false;
    base.reload();
    if (!compareMap(base.getModifiers(), expectedMods))
        return false;

    return true;
}
bool BaseDescriptionTests::BaseDescriptionWithMods()
{
    map<string, StatMod> expectedMods;
    expectedMods["Stat1"] = StatMod{1.0, 1.3};
    expectedMods["Stat2"] = StatMod{2.1, 1.6};
    BaseDescription base{"Name", expectedMods};

    if (base.getName() != "Name")
        return false;
    if (!compareMap(base.getModifiers(), expectedMods))
        return false;

    return true;
}
bool BaseDescriptionTests::BaseDescriptionWithModsReload()
{
    map<string, StatMod> expectedMods;
    expectedMods["Stat1"] = StatMod{1.0, 1.3};
    expectedMods["Stat2"] = StatMod{2.1, 1.6};
    BaseDescription base{"Name", expectedMods};

    if (base.getName() != "Name")
        return false;
    if (!compareMap(base.getModifiers(), expectedMods))
        return false;
    base.reload();
    if (!compareMap(base.getModifiers(), expectedMods))
        return false;

    return true;
}