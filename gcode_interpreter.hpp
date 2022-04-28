#include "cordinate.hpp"
#include "entities/command.hpp"
#include "entities/row.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class GcodeInterpreter {
private:
    // Stream for gcode file
    std::ifstream *file;

protected:
    // Current machine cordinates
    Cordinate pos;

    // Passing a line to the parser
    void executeLine(const std::string &line);
    // Parsing one line and returning the row
    Row parseLine(const std::string &line);

public:
    void openFile(const std::string &filename);
    void execute();
};