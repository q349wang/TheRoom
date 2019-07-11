#ifndef __CURSE_H__
#define __CURSE_H__
#include "Modifier.h"
#include "Item.h"
#include <string>

class Curse: public Modifier {
 public:
  Curse(Item *,float,float);
};

#endif