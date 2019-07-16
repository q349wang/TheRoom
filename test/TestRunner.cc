#include <iostream>

#include "ADTs/Command/CommandTests.h"
#include "ADTs/Item/BaseDescriptionTests.h"
#include "ADTs/Item/BlessingTests.h"

using namespace std;

int main()
{
    bool noFail = true;

    CommandTests commmandTests;
    BaseDescriptionTests baseDescriptionTests;
    BlessingTests blessingTests;

    if (!commmandTests.runTests())
    {
        noFail = false;
        cout << "Failed CommandTests" << endl;
    }

    if (!baseDescriptionTests.runTests())
    {
        noFail = false;
        cout << "Failed BaseDescriptionTests" << endl;
    }

    if (!blessingTests.runTests())
    {
        noFail = false;
        cout << "Failed BlessingTests" << endl;
    }

    if (noFail)
    {
        cout << "All tests passed!" << endl;
        return 0;
    }
    return 1;
}