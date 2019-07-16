#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include <memory>

class MapManager {
 private:
 protected:
 public:
    MapManager();
    ~MapManager();
    
    // To ensure map manager is not copy constructed
    MapManager(MapManager&) = delete;
};

#endif