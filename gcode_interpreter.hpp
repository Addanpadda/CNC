#include "cordinate.hpp"
#include "entities/command.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class GcodeInterpreter {
private:
    std::ifstream *file;

protected:
    Cordinate pos;

    void executeLine(const std::string &line);
    std::string clearSpaces(const std::string &str);
    int findEndOfNumber(const std::string &str, const int &start);
    std::vector<Command*> parseLine(const std::string &line);

public:
    void openFile(const std::string &filename);
    void execute();
};