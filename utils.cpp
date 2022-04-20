#include "utils.hpp"

int Utils::findEndOfNumber(const std::string &str, const int &start) {
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
}; 

std::string Utils::clearSpaces(const std::string &str) {
    std::string str2;

    for (int i = 0; i < str.length(); i++)
        if (str[i] != ' ') str2 += str[i];
    
    return str2;
}