#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../cordinate.hpp"
#include "axis.hpp"
#include "prirority.hpp"
#include <string>

// Ways of parsing, one parameter or cordinates as parameters
enum PARSE_METHOD {
    DIRECT, CORDINATES
};

class Command {
public:
    PRIRORITY prirority;
    PARSE_METHOD parseMethod;
};

namespace gcode {
    double directParse(const std::string &str, int &start);
    Cordinate cordinateParse(const std::string &str, int &start, Cordinate pos);

    class G00 : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::LAST;
        Cordinate pos;

        PARSE_METHOD parseMethod = PARSE_METHOD::CORDINATES;
    };

    class G01 : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::LAST;
        Cordinate pos;

        PARSE_METHOD parseMethod = PARSE_METHOD::CORDINATES;
    };

    class F : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::FIRST;
        double value;

       PARSE_METHOD parseMethod = PARSE_METHOD::DIRECT;
    };

    class T : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::FIRST;
        short value;

        PARSE_METHOD parseMethod = PARSE_METHOD::DIRECT;
    };
}

#endif