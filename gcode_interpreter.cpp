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
    std::vector<Command*> cmd = parseCommand(clearSpaces(line));
    
}

std::string GcodeInterpreter::clearSpaces(const std::string &str) {
    std::string str2;

    for (int i = 0; i < str.length(); i++)
        if (str[i] != ' ') str2 += str[i];
    
    return str2;
}

std::vector<Command*> GcodeInterpreter::parseCommand(const std::string &line) {
    std::vector<Command*> cmds;
    int s = 0;

    //e = line.find(" ");
    //if (e == -1) e = line.length();

    std::string gcmdstr = line.substr(s, s+3);
    std::string scmdstr = line.substr(s, s+1);

    if (gcmdstr == "G00") {
        cmds.push_back(new gcode::G00());

        s += 3;
    } else if (gcmdstr == "G01") {
        gcode::G01 *cmd = new gcode::G01();
        cmd->pos.x = this->pos.x;
        cmd->pos.y = this->pos.y;
        cmd->pos.z = this->pos.z;

        s += 3;

        while(true) {
            char cmdchar = toupper(line[s]);

            if (cmdchar == 'X') {

            } else if (cmdchar == 'Y') {

            } else if (cmdchar == 'Z') { 
            
            } else break;
        }

        cmds.push_back(cmd);
        
    } else if (scmdstr == "F") {
        cmds.push_back(new gcode::F());
        s += 1;
    } else if (scmdstr == "T") {
        cmds.push_back(new gcode::T());
        s += 1;
    }

    std::cout << gcmdstr << std::endl;
    std::cout << scmdstr << std::endl;
    
    //s = e + 1;


    return cmds;
}