#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include "../ADTs/Map/Map.h"

#include <memory>
#include <map>

class EnemyConf;
class ItemManager;
class EnemyManager;

class MapManager {
 private:
    std::map<std::string, EnemyConf> enemy_configuration_;

    std::unique_ptr<ItemManager> item_manager;
    std::unique_ptr<EnemyManager> enemy_manager;
 protected:
 public:
    // Constructor which takes enemy configuration information
    MapManager(std::map<std::string, EnemyConf>);

    //Default destructor
    ~MapManager();

    // To ensure map manager is not copy constructed
    MapManager(MapManager&) = delete;

    // Populates a map with enemies & items
    // Scalling with the map level
    void populateMap(std::shared_ptr<Map>&, int);

   // Adds item to map at location
    void addItem(std::shared_ptr<Map>&, int, std::pair<int, int>);
};

#endif