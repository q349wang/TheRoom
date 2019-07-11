#include <string>
#include <StatMod.h>

StatMod::StatMod(float _adder, float _multiplier) :
adder{_adder}, multiplier{_multiplier} {}
StatMod::~StatMod(){}
float StatMod::getAdder(){
    return adder;
}
float StatMod::getMultiplier(){
    return multiplier;
}