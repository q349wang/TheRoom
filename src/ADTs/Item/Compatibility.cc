#include "Compatibility.h"
#include <string>
using namespace std;

Compatability::Compatability(Item * name,string className): Modifier{name} {
    component->updateName(className);
}