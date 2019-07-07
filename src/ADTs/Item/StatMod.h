#ifndef _ROOM_H_
#define _ROOM_H_
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
};

#endif