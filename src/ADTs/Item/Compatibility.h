#ifndef __COMPATIBILITY_H__
#define __COMPATIBILITY_H__
#include "Modifier.h"

/**
 * Class that represents how well an
 * item can be used by a given class
 */
class Compatability: public Modifier {
  std::string heroClass;
  StatMod stat;
 public:
  Compatability(std::string, StatMod, std::shared_ptr<ItemDescription>);
  ~Compatability();
  std::string getName() const override;
  std::map<std::string, StatMod>& getModifiers() override;
};

#endif
