#include "gcode_interpreter.hpp"

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

void GcodeInterpreter::executeLine(const std::string &line) {
    std::cout << "Executing: " << line << std::endl;
    std::vector<Command*> cmd = parseLine(line);
    
}

std::string GcodeInterpreter::clearSpaces(const std::string &str) {
    std::string str2;

    for (int i = 0; i < str.length(); i++)
        if (str[i] != ' ') str2 += str[i];
    
    return str2;
}

int GcodeInterpreter::findEndOfNumber(const std::string &str, const int &start) {
    for (int i = start; i < str.length(); i++)
        if (str[i] != '0' && 
            str[i] != '1' && 
            str[i] != '2' && 
            str[i] != '3' && 
            str[i] != '4' && 
            str[i] != '5' && 
            str[i] != '6' && 
            str[i] != '7' && 
            str[i] != '8' && 
            str[i] != '9' && 
            str[i] != '-' && 
            str[i] != '.') return i-1;
    
    return str.length()-1;
}

std::vector<Command*> GcodeInterpreter::parseLine(const std::string &line) {
    std::string str = clearSpaces(line);
    std::vector<Command*> cmds;
    int s = 0;

    //e = str.find(" ");
    //if (e == -1) e = str.length();


    while (s < str.length()) {
        std::string gcmdstr = str.substr(s, 3);
        std::string scmdstr = str.substr(s, 1);

        if (gcmdstr == "G00") {
            cmds.push_back(new gcode::G00());

            s += 3;
        } else if (gcmdstr == "G01") {
            // Move past the G01 string
            s += 3;
            
            // Initiate the command and copy CNC current
            // cordinates if some axis does not change
            gcode::G01 *cmd = new gcode::G01();
            cmd->pos.x = this->pos.x;
            cmd->pos.y = this->pos.y;
            cmd->pos.z = this->pos.z;

        
            // Collect all data (x, y, z) that is connected to G01
            while (true) {
                char cmdchar = toupper(str[s]);
                double *cordptr;

                if (cmdchar == 'X') {
                    cordptr = &cmd->pos.x;
                } else if (cmdchar == 'Y') {
                    cordptr = &cmd->pos.y;
                } else if (cmdchar == 'Z') {
                    cordptr = &cmd->pos.z;
                } else break;

                int end = findEndOfNumber(str, s+1);
                double value = std::stod(str.substr(s+1, end-s));
                s = end+1;

                *cordptr = value;
            }

            std::cout << "[G01]" << "\tX: " << cmd->pos.x << "\tY: " << cmd->pos.y << "\tZ: " << cmd->pos.z << std::endl;
            cmds.push_back(cmd);
            
        } else if (scmdstr == "F") {
            gcode::F *cmd = new gcode::F();

            int end = findEndOfNumber(str, s+1);
            cmd->value = std::stod(str.substr(s+1, end-s));
            s = end+1;
            
            std::cout << "[F]\t" << cmd->value << std::endl;
            cmds.push_back(cmd);
        } else if (scmdstr == "T") {
            gcode::T *cmd = new gcode::T();

            int end = findEndOfNumber(str, s+1);
            cmd->value = std::stoi(str.substr(s+1, end-s));
            s = end+1;
            
            std::cout << "[T]\t" << cmd->value << std::endl;
            cmds.push_back(cmd);
        } else s++;
    }

    return cmds;
}