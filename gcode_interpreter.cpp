#include "gcode_interpreter.hpp"
#include "utils.hpp"


void GcodeInterpreter::openFile(const std::string &filename) {
        file = new std::ifstream(filename);
    }

void GcodeInterpreter::execute() {
    if (!file->is_open()) throw("Can't execute before opening file");

    std::string line;
    while(std::getline(*file, line)) {
        executeLine(line);
    }
}

// Can be used to execute line by line with a row
void GcodeInterpreter::executeLine(const std::string &line) {
    std::cout << "Executing: " << line << std::endl;
    Row row = parseLine(line);
    
}

// Parsing one line
Row GcodeInterpreter::parseLine(const std::string &line) {
    std::string str = Utils::clearSpaces(line);
    Row row;
    std::vector<Command*> cmds;
    int s = 0;

    while (s < str.length()) {
        // Two kinds of commands, single and three character commands
        std::string gcmdstr = str.substr(s, 3);
        std::string scmdstr = str.substr(s, 1);

        // Checking what command and parse it
        if (gcmdstr == "G00") {
            // Initiate the command and copy CNC current
            gcode::G00 *cmd = new gcode::G00();
            cmd->pos = gcode::cordinateParse(str, s, pos);

            std::cout << "[G00]" << "\tX: " << cmd->pos.x << "\tY: " << cmd->pos.y << "\tZ: " << cmd->pos.z << std::endl;
            cmds.push_back(cmd);
        } else if (gcmdstr == "G01") {
            // Initiate the command and copy CNC current
            gcode::G01 *cmd = new gcode::G01();
            cmd->pos = gcode::cordinateParse(str, s, pos);

            std::cout << "[G01]" << "\tX: " << cmd->pos.x << "\tY: " << cmd->pos.y << "\tZ: " << cmd->pos.z << std::endl;
            cmds.push_back(cmd);
        } else if (scmdstr == "F") {
            // Initiate the command and copy CNC current
            gcode::F *cmd = new gcode::F();

            cmd->value = gcode::directParse(str, s);
            
            std::cout << "[F]\t" << cmd->value << std::endl;
            cmds.push_back(cmd);
        } else if (scmdstr == "T") {
            gcode::T *cmd = new gcode::T();

            cmd->value = gcode::directParse(str, s);           
            
            std::cout << "[T]\t" << cmd->value << std::endl;
            cmds.push_back(cmd);
        } else s++;
    }

    row.cmds = cmds;
    return row;
}
