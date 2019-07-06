#include <vector>

class Command {
    char cmd;
    std::vector<char> args;
    public:
    Command(char);
    Command(char, std::vector<char>);

    const char& getCommand() const;
    const std::vector<char>& getArgs() const;
};