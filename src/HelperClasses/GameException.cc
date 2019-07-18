#include "GameException.h"

using namespace std;

GameException::GameException(string msg) : msg{msg} {}

string GameException::what() { return msg; }