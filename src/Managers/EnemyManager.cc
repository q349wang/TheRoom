#include "EnemyManager.h"
#include "../ADTs/Entity/Ground.h"
#include "../ADTs/Entity/Flying.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

/**
 * Signature: EnemyManager(map<string, EnemyConfig>)
 * Purpose: Constructs a map manager which will provide scaled enemies
 *          dependent on the congfiguration information initially provided
 */
EnemyManager::EnemyManager(map<string, EnemyConfig> configuration): 
ground_scaling{configuration.at("Ground")}, flying_scaling{configuration.at("Flying")} {}

/**
 * Signature: ~EnemyManager()
 * Purpose: Default Destructor
 */
EnemyManager::~EnemyManager(){}

/**
 * Signature: shared_ptr<Enemy> createEnemy(int, pair<int, int>)
 * Purpose: Constructs and provided an enemy scaled to
 *          the specified level
 */
shared_ptr<Enemy> createEnemy(int level, pair<int, int> location) {
    // Create seed for psuedorandom number
    srand(time(NULL));
    int random_selection = rand() % (ground_scaling_.weight + flying_scaling_.weight);

    if(random_selection < ground_scaling_.weight) {
        return make_shared(Ground{(ground_scaling_.health.first + (ground_scaling_.health.second * level)),
                                  (ground_scaling_.energy.first + (ground_scaling_.energy.second * level)),
                                  (ground_scaling_.attack.first + (ground_scaling_.attack.second * level)),
                                  (ground_scaling_.armour.first + (ground_scaling_.armour.second * level)), 
                                  location});
    }
    else {
        return make_shared(Flying{(flying_scaling_.health.first + (flying_scaling_.health.second * level)),
                            (flying_scaling_.energy.first + (flying_scaling_.energy.second * level)),
                            (flying_scaling_.attack.first + (flying_scaling_.attack.second * level)),
                            (flying_scaling_.armour.first + (flying_scaling_.armour.second * level)), 
                            location});
    }
}