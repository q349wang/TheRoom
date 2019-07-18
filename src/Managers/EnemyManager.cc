#include "EnemyManager.h"
#include "../ADTs/Entity/Ground.h"
#include "../ADTs/Entity/Flying.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

/**
 * Signature: EnemyManager(map<string, EnemyConf>)
 * Purpose: Constructs a map manager which will provide scaled enemies
 *          dependent on the congfiguration information initially provided
 */
EnemyManager::EnemyManager(map<string, EnemyConf> configuration) : ground_scaling_{configuration.at("Ground")}, flying_scaling_{configuration.at("Flying")} {
        // Create seed for psuedorandom number
    srand(time(NULL));
}

/**
 * Signature: ~EnemyManager()
 * Purpose: Default Destructor
 */
EnemyManager::~EnemyManager() {}

/**
 * Signature: shared_ptr<Enemy> createEnemy(int, pair<int, int>)
 * Purpose: Constructs and provided an enemy scaled to
 *          the specified level
 */
shared_ptr<Enemy> EnemyManager::createEnemy(int level, pair<int, int> location)
{
    int random_selection = rand() % (ground_scaling_.weight + flying_scaling_.weight);
    cout << "rand" << random_selection << endl;
    cout << "location "<< location.first << " " << location.second << endl;
    if (random_selection < ground_scaling_.weight)
    {
        shared_ptr<Ground> enemy = make_shared<Ground>((ground_scaling_.health.first + (ground_scaling_.health.second * level)),
                                                       (ground_scaling_.energy.first + (ground_scaling_.energy.second * level)),
                                                       (ground_scaling_.attack.first + (ground_scaling_.attack.second * level)),
                                                       (ground_scaling_.armour.first + (ground_scaling_.armour.second * level)),
                                                       location);
        return enemy;
    }
    else
    {
        shared_ptr<Flying> enemy = make_shared<Flying>((flying_scaling_.health.first + (flying_scaling_.health.second * level)),
                                                       (flying_scaling_.energy.first + (flying_scaling_.energy.second * level)),
                                                       (flying_scaling_.attack.first + (flying_scaling_.attack.second * level)),
                                                       (flying_scaling_.armour.first + (flying_scaling_.armour.second * level)),
                                                       location);
        return enemy;
    }
}