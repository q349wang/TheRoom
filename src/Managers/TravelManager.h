#ifndef TRAVEL_MANAGER_
#define TRAVEL_MANAGER_

#include "../HelperClasses/Subject.h"
#include <sstream>
#include <memory>

class Map;
class Player;
class Command;

class TravelManager : public Subject {
    std::weak_ptr<Map> map;
    std::weak_ptr<Player> player;

    bool toExit;
    bool toBattle;
    public:
    TravelManager(std::shared_ptr<Map>, std::shared_ptr<Player>);
    ~TravelManager();
    // No copying TravelManager
    TravelManager(const TravelManager&) = delete;

    void makeMove(const Command&);
    void startTravel();
    void runTravel();

    const std::weak_ptr<Map> getMap() const;

    bool isExiting() const;
};
#endif
