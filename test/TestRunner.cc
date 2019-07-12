#include <iostream>

#include "ADTs/Command/CommandTests.h"
#include "ADTs/Item/BaseDescriptionTests.h"

using namespace std;

int main()
{
    bool noFail = true;

    CommandTests commmandTests;
    BaseDescriptionTests baseDescriptionTests;

    if (!commmandTests.runTests())
    {
        cout << "Failed CommandTests" << endl;
    }

    if (!baseDescriptionTests.runTests())
    {
        cout << "Failed BaseDescriptionTests" << endl;
    }

    if (noFail)
    {
        cout << "All tests passed!" << endl;
        return 0;
    }
    return 1;
}