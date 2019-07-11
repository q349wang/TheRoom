#ifndef _STAT_MOD_H_
#define _STAT_MOD_H_
#include <string>
#include <unordered_set>
using namespace std;

class StatMod {
    float adder;
    float multiplier;
    unordered_set <string> classes;
    public:
        StatMod(float,float);
        ~StatMod();
        float getAdder();
        float getMultiplier();
};

#endif