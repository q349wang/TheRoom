#include "Compatibility.h"
#include <string>
using namespace std;

Compatability::Compatability(Item * name): Modifier{name} {
    component->updateName("Class name");
}