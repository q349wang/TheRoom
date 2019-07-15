#ifndef __CURSE_H__
#define __CURSE_H__
#include "Modifier.h"


/**
 * Class that represents debuffs
 * The debuffs are stored as positive numbers
 * These are subtracted from the modifer list at runtime
 */
class Curse: public Modifier {
  std::string name;
  StatMod stat;
 public:
  Curse(std::string, StatMod, std::shared_ptr<ItemDescription>);
  ~Curse();
  std::string getName() const override;
  std::map<std::string, StatMod>& getModifiers() override;
};

#endif