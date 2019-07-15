#include "Command.h"

Command::Command(char cmd) : cmd{cmd}, args{} {}
Command::Command(char cmd, std::vector<std::string> args) : cmd{cmd}, args{args} {}

const char &Command::getCommand() const
{
    return cmd;
}
const std::vector<std::string> &Command::getArgs() const
{
    return args;
}