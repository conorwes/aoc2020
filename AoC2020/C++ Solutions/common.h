#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

inline std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);

    std::string worker;
    while (std::getline(ss, worker, delimiter)) {
        tokens.push_back(worker);
    }

    return tokens;
}

inline std::string trim(std::string str) {
    size_t beginPos = str.find_first_not_of(" \t");
    if (beginPos == std::string::npos) {
        return "";
    }

    size_t endPos = str.find_last_not_of(" \t");
    size_t len = endPos - beginPos + 1;

    return str.substr(beginPos, len);
}