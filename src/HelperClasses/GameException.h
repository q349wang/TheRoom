#ifndef GAME_EXCEPTION_H_
#define GAME_EXCEPTION_H_

#include <string>

class GameException {
    std::string msg;
    public:
    GameException(std::string);
    std::string what();
};

#endif