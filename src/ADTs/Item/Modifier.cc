#include "Item.h"
#include "Modifier.h"

using namespace std;

Modifier::Modifier(Item * item): component{item}{}
Modifier::~Modifier() {}
