#ifndef ROW_HPP
#define ROW_HPP
#include "command.hpp"
#include <vector>

// A line in the gcode document
struct Row {
    int n;
    std::vector<Command*> cmds;
};

#endif