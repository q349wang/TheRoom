#include <iostream>

#include "ADTs/Command/CommandTests.h"

using namespace std;

int main() {
    bool noFail = true;

    CommandTests commmandTests;
    
    if (!commmandTests.runTests()) {
        cout << "Failed CommandTests" << endl;
    }

    if (noFail) cout << "All tests passed!" << endl;
}