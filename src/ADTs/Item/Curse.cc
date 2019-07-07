#include "Curse.h"
#include <string>
using namespace std;

Curse::Curse(Item *_component): Modifier{_component} {
    component->updateName("Curse");
}