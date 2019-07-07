#include "Compatibility.h"
#include <string>
using namespace std;

Compatability::Compatability(Item *_component): Modifier{_component} {
    component->updateName("Class name");
}