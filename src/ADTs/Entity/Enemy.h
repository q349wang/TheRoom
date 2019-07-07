#ifndef ENEMY_H_
#define ENEMY_H_

#include <string>

#include "Entity.h"

class Enemy: public Entity {
 private:
 protected:
 public:
 std::string getName() const;
};

#endif