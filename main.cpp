#include <iostream>
#include "CNC.hpp"

CNC cnc;

int main(int argc, char *argv[]) {
    cnc.openFile("test.gcode");
    cnc.execute();

    return 0;
}