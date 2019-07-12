#ifndef __COMPATIBILITY_H__
#define __COMPATIBILITY_H__
#include "Modifier.h"

class Compatability: public Modifier {
  std::string heroClass;
  StatMod stat;
 public:
  Compatability(std::string, StatMod, std::shared_ptr<ItemDescription>);
  ~Compatability();
  std::string getName() override;
  map<std::string, StatMod>& getModifiers() override;
};

#endif