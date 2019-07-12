#ifndef COMMAND_TESTS_H_
#define COMMAND_TESTS_H_

#include "../../TestsBase.h"

class CommandTests : public Tests {
    public:
    CommandTests();
    ~CommandTests();
    bool runTests() override;
    bool CommandNoArgs();
    bool CommandEmptyArgs();
    bool CommandWithArgs();
};

#endif