#include "StatMod.h"
#include <string>

StatMod::StatMod(double _adder, double _multiplier)
    : adder{_adder}, multiplier{_multiplier} {}

StatMod::StatMod(StatMod first, StatMod second)
    : adder{first.adder + second.adder},
      multiplier{first.multiplier + second.multiplier} {}

StatMod::~StatMod() {}
double StatMod::getAdder() { return adder; }
double StatMod::getMultiplier() { return multiplier; }

// We have a resolution of 0.1 for stat modifiers
bool StatMod::isNone() { return abs(adder) < 0.1 && abs(multiplier) < 0.1; }