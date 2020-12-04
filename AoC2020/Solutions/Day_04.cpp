
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// valid fields
// byr - required
// iyr - required
// eyr - required
// hgt - required
// hcl - required
// ecl - required
// pid - required
// cid - optional if all other fields present

// Function to process the input into individual ID chunks. We'll process those later
std::vector<std::string> parseInformation(const std::string& info) {
    std::string workItem = info; // might not need this...
    std::string delimiter = "\n\n";

    size_t pos = 0;
    std::vector<std::string> tokens;

    while ((pos = workItem.find(delimiter)) != std::string::npos) {
        tokens.push_back(workItem.substr(0, pos));
        workItem.erase(0, pos + delimiter.length());
    }

    return tokens;
}

int main() {
    std::ifstream in("../Inputs/Day_04.txt");
    std::string buf, info;
    while (std::getline(in, buf)) {
        info.append(buf);
    }

    auto tokens = parseInformation(info);

    for (auto i : tokens)
    {
        std::cout << i << std::endl;
    }

   //std::cout << "Part One: " << partOne(vec) << std::endl;
   //std::cout << "Part Two: " << partTwo(vec) << std::endl;

   return 0;
}