#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../cordinate.hpp"
#include "axis.hpp"
#include "prirority.hpp"

class Command {
public:
    PRIRORITY prirority;
};

namespace gcode {
    class G00 : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::LAST;
        Cordinate pos;
    };

    class G01 : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::LAST;
        Cordinate pos;
    };

    class F : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::FIRST;
    };

    class T : public Command {
    public:
        PRIRORITY prirority = PRIRORITY::FIRST;
    };
}

#endif