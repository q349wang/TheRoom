#ifndef __BLESSING_H__
#define __BLESSING_H__
#include "Modifier.h"
#include "Item.h"
#include <string>

class Blessing: public Modifier {
 public:
  Blessing(Item *,float,float);
};

#endif