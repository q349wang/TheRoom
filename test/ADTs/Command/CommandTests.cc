#include "CommandTests.h"
#include "../../../src/ADTs/Command/Command.h"

using namespace std;

CommandTests::CommandTests() {}
CommandTests::~CommandTests() {}

bool CommandTests::CommandNoArgs()
{
    Command cmd{'U'};

    vector<string> expected;
    return cmd.getCommand() == 'U' && cmd.getArgs() == expected;
}

bool CommandTests::CommandEmptyArgs()
{
    vector<string> args;
    vector<string> expected;

    Command cmd{'U', args};
    return cmd.getCommand() == 'U' && cmd.getArgs() == expected;
}

bool CommandTests::CommandWithArgs()
{
    vector<string> args = {"arg1", "arg2"};
    vector<string> expected = {"arg1", "arg2"};

    Command cmd{'U', args};
    return cmd.getCommand() == 'U' && cmd.getArgs() == expected;
}

bool CommandTests::runTests()
{
    bool noFail = true;

    // Command with no arguments
    if (!CommandNoArgs())
    {
        cout << "Failed CommandNoArgs" << endl;
        noFail = false;
    }

        // Command with no arguments
    if (!CommandWithArgs())
    {
        cout << "Failed CommandWithArgs" << endl;
        noFail = false;
    }

        // Command with no arguments
    if (!CommandEmptyArgs())
    {
        cout << "Failed CommandEmptyArgs" << endl;
        noFail = false;
    }

    return noFail;
}