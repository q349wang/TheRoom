#ifndef __CURSE_H__
#define __CURSE_H__
#include "Modifier.h"

class Curse: public Modifier {
  std::string name;
  StatMod stat;
 public:
  Curse(std::string, StatMod, std::shared_ptr<ItemDescription>);
  ~Curse();
  std::string getName() override;
  map<std::string, StatMod>& getModifiers() override;
};

#endif