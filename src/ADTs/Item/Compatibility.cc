#include "Compatibility.h"
#include <string>
using namespace std;

Compatability::Compatability(string name): Modifier{name} {
    component->updateName("Class name");
}