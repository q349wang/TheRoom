#include "Item.h"
#include "Modifier.h"

using namespace std;

Modifier::Modifier(string placeholder): Item{placeholder}{}
Modifier::~Modifier() {delete component;}