#include "Item.h"
#include "Modifier.h"

Modifier::Modifier(Item *_component): component{_component} {};
Modifier::~Modifier() {delete component;}