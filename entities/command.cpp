#include "command.hpp"
#include "../utils.hpp"

double gcode::directParse(const std::string &str, int &start) {
    start += 1;

    int end = Utils::findEndOfNumber(str, start);
    double value = std::stod(str.substr(start, end-start+1));
    start = end+1;
    
    return value;
}

Cordinate gcode::cordinateParse(const std::string &str, int &start, Cordinate pos) {
    start += 3;

    // Collect all data (x, y, z) that is connected to G01
    while (true) {
        char cmdchar = toupper(str[start]);
        double *cordptr;

        if (cmdchar == 'X') {
            cordptr = &pos.x;
        } else if (cmdchar == 'Y') {
            cordptr = &pos.y;
        } else if (cmdchar == 'Z') {
            cordptr = &pos.z;
        } else break;

        int end = Utils::findEndOfNumber(str, start+1);
        double value = std::stod(str.substr(start+1, end-start));
        start = end+1;

        *cordptr = value;
    }

    return pos;
}