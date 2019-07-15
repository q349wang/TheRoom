#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include <string>

/* ADT which stores the command and arguments of a command
 * inputted by user into stdin
 */
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
