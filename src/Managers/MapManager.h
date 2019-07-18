#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include "../ADTs/Map/Map.h"

#include <memory>

class MapManager {
 private:
    std::map<std::string, EnemyConfig> enemy_configuration_;
 protected:
 public:
    // Constructor which takes enemy configuration information
    MapManager(std::map<std::string, EnemyConfig>);

    //Default destructor
    ~MapManager();

    // To ensure map manager is not copy constructed
    MapManager(MapManager&) = delete;

    // Populates a map with enemies & items
    // Scalling with the map level
    void populateMap(std::shared_ptr<Map>, int);
};

#endif