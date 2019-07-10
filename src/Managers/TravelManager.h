#ifndef TRAVEL_MANAGER_
#define TRAVEL_MANAGER_

#include "../HelperClasses/Subject.h"
#include <sstream>

class Map;
class Player;
class Command;

class TravelManager : public Subject {
    Map* map;
    Player* player;

    bool toBattle;
    public:
    TravelManager(Map*, Player*);
    ~TravelManager();
    // No copying TravelManager
    TravelManager(const TravelManager&) = delete;

    void makeMove(const Command&);
    void startTravel();
    void runTravel();

    const Map* getMap() const;
};
#endif
