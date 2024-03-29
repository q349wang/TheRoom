#ifndef __BLESSING_H__
#define __BLESSING_H__
#include "Modifier.h"

/**
 * Represents a buff modifier (Blessing)
 */
class Blessing: public Modifier {
  std::string name;
  StatMod stat;
 public:
  Blessing(std::string, StatMod, std::shared_ptr<ItemDescription>);
  ~Blessing();
  std::string getName() const override;
  std::map<std::string, StatMod>& getModifiers() override;
};

#endif
