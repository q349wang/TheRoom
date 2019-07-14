#ifndef TESTS_H_
#define TESTS_H_

#include <iostream>

#include <map>
#include <string>

class StatMod;

class Tests
{
public:
    bool compareMap(std::map<std::string, StatMod>, std::map<std::string, StatMod>);
    virtual ~Tests() = 0;
    virtual bool runTests() = 0;
};

#endif