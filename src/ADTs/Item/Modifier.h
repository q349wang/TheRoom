#ifndef _MODIFIER_H_
#define _MODIFIER_H_
#include "Item.h"

class Modifier: public Item {
 protected:
  Item *component;
 public:
  Modifier(Item *component);
  virtual ~Modifier();
};

#endif