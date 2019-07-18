#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include "../ADTs/Map/Map.h"

#include <memory>

class MapManager {
 private:
 protected:
 public:
    // Default constructor
    MapManager();

    //Default destructor
    ~MapManager();

    // To ensure map manager is not copy constructed
    MapManager(MapManager&) = delete;

    // Populates a map with enemies & items
    // Scalling with the map level
    void populateMap(std::shared_ptr<Map>, int);
};

#endif