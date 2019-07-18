#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

#include "../ADTs/Entity/Enemy.h"
#include "../ADTs/Entity/EnemyConf.h"

#include <map>

class EnemyManager {
 private:
    // Maintains enemy scalling/configuration information
    EnemyConf ground_scaling_, flying_scaling_;

 protected:
 public:
    // Constructor requires a map of enemy types and their
    // respective configuration
    EnemyManager(std::map<std::string, EnemyConf>);

    // Default destructor
    ~EnemyManager();

    // Creates an enemy scaled to the specified level
    std::shared_ptr<Enemy> createEnemy(int, std::pair<int, int>);
};

#endif