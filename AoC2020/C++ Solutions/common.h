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