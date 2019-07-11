#ifndef __COMPATIBILITY_H__
#define __COMPATIBILITY_H__
#include "Modifier.h"
#include "Item.h"
#include <string>

class Compatability: public Modifier {
 public:
  Compatability(Item *,std::string);
};

#endif