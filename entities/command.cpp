#include "command.hpp"
#include "../utils.hpp"

double gcode::directParse(const std::string &str, int &start) {
    start += 1; // Skip past command (usually single character)

    // Extract the double cordinate value
    int end = Utils::findEndOfNumber(str, start);
    double value = std::stod(str.substr(start, end-start+1));
    start = end+1;
    
    return value;
}

Cordinate gcode::cordinateParse(const std::string &str, int &start, Cordinate pos) {
    start += 3; // Skip past command (usually 3 characters)

    // Collect all data (x, y, z) that is connected to command
    while (true) {
        // x, y or z
        char cmdchar = toupper(str[start]);
        // Pointer to the cordinate axis so it can be set after 
        // the if statements so break runs before findEndOfNumber
        double *cordptr;

        if (cmdchar == 'X') {
            cordptr = &pos.x;
        } else if (cmdchar == 'Y') {
            cordptr = &pos.y;
        } else if (cmdchar == 'Z') {
            cordptr = &pos.z;
        } else break;

        // Extract the double cordinate value
        int end = Utils::findEndOfNumber(str, start+1);
        double value = std::stod(str.substr(start+1, end-start));
        start = end+1;

        *cordptr = value;
    }

    return pos;
}