#ifndef TESTS_H_
#define TESTS_H_

#include <iostream>

class Tests {
    public:
    virtual ~Tests() = 0;
    virtual bool runTests() = 0;
};

#endif