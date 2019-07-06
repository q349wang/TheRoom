#include "Command.h"

Command::Command(char cmd): cmd{cmd}, args{} {}
Command::Command(char cmd, std::vector<char> args): cmd{cmd}, args{args} {}