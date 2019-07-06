#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include <string>

class Command {
    char cmd;
    std::vector<std::string> args;
    public:
    Command(char);
    Command(char, std::vector<std::string>);

    const char& getCommand() const;
    const std::vector<std::string>& getArgs() const;
};
#endif
