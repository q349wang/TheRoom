#ifndef TRAVEL_MANAGER_
#define TRAVEL_MANAGER_

#include "../HelperClasses/Subject.h"
#include <sstream>

class Map;
class Player;

class TravelManager : public Subject {
    Map* map;
    Player* player;

    bool toBattle;
    std::ostringstream msg;
    public:
    TravelManager(Map*, Player*);
    ~TravelManager();
    // No copying TravelManager
    TravelManager(const TravelManager&) = delete;

    void makeMove();
    void startTravel();
    void runTravel();
};
#endif
