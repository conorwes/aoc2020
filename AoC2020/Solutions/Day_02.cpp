
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <tuple>

// Function to take a line of input and parse out the relevant information.
// We expect the line to be in the form of X-Y Z: AAA, where X is min, Y is max, Z is char, and AAA is string
std::tuple<int, int, char, std::string> parseInformation(const std::string& input) {

    // first get min value
    int startPos = 0;
    int endPos = input.find('-');
    int minVal = stoi(input.substr(startPos, endPos));

    // next get max value
    startPos = endPos + 1;
    endPos = input.find(' ');
    int maxVal = stoi(input.substr(startPos, endPos));

    // next get key
    char key = input[endPos + 1];

    // finally get password
    std::string password = input.substr(endPos + 4, std::string::npos);

    return std::make_tuple(minVal, maxVal, key, password);
}

// Function to determine whether the requirements for part one have been satisfied.
// Part one requires that the occurrences of the key char falls within the specified min and max values.
bool satisfiesRequirementsPartOne(const std::tuple<int, int, char, std::string>& info) {

    // Retrieve values from our tuple
    auto minVal = std::get<0>(info);
    auto maxVal = std::get<1>(info); 
    auto key = std::get<2>(info);
    auto password = std::get<3>(info);

    // Simply leverage std::count to get our total, and then compare
    auto count = std::count(password.begin(), password.end(), key);
    if (count < minVal || count > maxVal)
        return false;

    return true;
}

// Function to determine whether the requirements for part two have been satisfied.
// Part two requires that the key char is present either at the min index or the max index.
bool satisfiesRequirementsPartTwo(const std::tuple<int, int, char, std::string>& info) {

    // Retrieve values from our tuple
    auto firstIndex = std::get<0>(info) - 1; // no concept of zero-index, so decrease by one
    auto secondIndex = std::get<1>(info) - 1;
    auto key = std::get<2>(info);
    auto password = std::get<3>(info);

    // Be cheeky and sum up the bools as ints. Anything != 1 means both indices either are or are not the key, thus bad.
    int sum = (int)(password[firstIndex] == key) + (int)(password[secondIndex] == key);
    if (sum != 1)
        return false;

    return true;
}

// Part one: determine if key char is present in required amount.
int partOne(const std::vector<std::string>& vec) {
    std::vector<std::tuple<int, int, char, std::string>> information;

    for (auto i : vec) {
        information.push_back(parseInformation(i));
    }

    int validCount;
    for (auto i : information) {
        if (satisfiesRequirementsPartOne(i))
            validCount++;
    }

    return validCount;
}


// Part two: determine if key char is present at one of the specified indices.
int partTwo(const std::vector<std::string>& vec) {
    std::vector<std::tuple<int, int, char, std::string>> information;

    for (auto i : vec) {
        information.push_back(parseInformation(i));
    }

    int validCount;
    for (auto i : information) {
        if (satisfiesRequirementsPartTwo(i))
            validCount++;
    }

    return validCount;
}

int main() {
    std::ifstream in("../Inputs/Day_02.txt");
    std::string buf;
    std::vector<std::string> vec;
    while (std::getline(in, buf)) {
        vec.push_back(buf);
    }

   std::cout << "Part One: " << partOne(vec) << std::endl;
   std::cout << "Part Two: " << partTwo(vec) << std::endl;

   return 0;
}