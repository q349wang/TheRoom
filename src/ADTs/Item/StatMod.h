#ifndef _STAT_MOD_H_
#define _STAT_MOD_H_
#include <string>
#include <unordered_set>

class StatMod {

    double adder;
    double multiplier;
    public:
        StatMod(double adder = 0,double multiplier = 0);
        StatMod(StatMod, StatMod);
        ~StatMod();
        double getAdder();
        double getMultiplier();
        bool isNone();

        bool operator==(const StatMod&);
};

#endif