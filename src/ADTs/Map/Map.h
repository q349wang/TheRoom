#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include <vector>
#include <memory>

class Map {
 private:
    std::pair<int,int> start_;
    std::vector<std::vector<Tile*>> map_;

 protected:
 public:
    Map();
    ~Map();
};

#endif