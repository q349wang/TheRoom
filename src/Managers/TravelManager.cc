#include "TravelManager.h"
#include "../../ADTs/Entity/Player.h"
TravelManager::TravelManager(Map* map, Player* player):
    player{player},
    map{map}
    {}
void TravelManager::makeMove() {

}

void TravelManager::startTravel() {

    runTravel();
}

void TravelManager::runTravel() {
    while(!map->OnEnemy()) {

    }
}