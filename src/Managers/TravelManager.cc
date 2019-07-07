#ifndef TRAVEL_MANAGER_
#define TRAVEL_MANAGER_

#include "../HelperClasses/Subject.h"

class Map;
class Player;

class TravelManager : public Subject {
    Map* map;
    Player* player;
    public:
    TravelManager(Map*, Player*);
    ~TravelManager();

    void makeMove();
    void runTravel();
};
#endif
