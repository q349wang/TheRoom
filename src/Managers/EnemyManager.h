#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

#include "Enemy.h"

#include <map>

class EnemyManager {
 private:
    // Maintains enemy scalling/configuration information
    EnemyConfig ground_scaling_, flying_scaling_;

 protected:
 public:
    // Constructor requires a map of enemy types and their
    // respective configuration
    EnemyManager(std::map<std::string, EnemyConfig>);

    // Default destructor
    ~EnemyManager();

    // Creates an enemy scaled to the specified level
    std::shared_ptr<Enemy> createEnemy(int, std::pair<int, int>);
};

#endif