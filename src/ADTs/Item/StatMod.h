#ifndef _STAT_MOD_H_
#define _STAT_MOD_H_
#include <string>
#include <unordered_set>


/**
 * Stores the adder and
 * multiplier information for
 * a single stat
 */
class StatMod {

    double adder;
    double multiplier;
    public:
        StatMod(double adder = 0,double multiplier = 0);
        StatMod(StatMod, StatMod);
        ~StatMod();
        double getAdder() const;
        double getMultiplier() const;
        bool isNone() const;

        bool operator==(const StatMod&) const;
};

#endif