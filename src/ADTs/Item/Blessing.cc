#include "Blessing.h"
#include <string>
using namespace std;

Blessing::Blessing(Item *_component): Modifier{_component} {
    component->updateName("Blessing");
};