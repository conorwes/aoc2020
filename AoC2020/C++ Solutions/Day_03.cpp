#include "common.h"
#include <list>

// Function to count the number of trees encountered by a specified slope
int countTrees(const std::vector<std::vector<char>>& map, int deltaHoriz, int deltaVert) {
    int horiz(0), vert(0); // track horizontal and vertical position
    int treeCount; // track number of trees we've encountered

    // first time doing a do/while loop!
    do {
        if (map.at(vert).at(horiz) == '#' ) {
            treeCount++;
        }
        horiz += deltaHoriz;
        vert += deltaVert;
        horiz = horiz % map[0].size(); // do simple modulus to repeat the pattern
    } while (vert < map.size());

    return treeCount;
}

// Part one is pretty straightforward - just run through countTrees with the provided slope.
int partOne(const std::vector<std::vector<char>>& map) {
    return countTrees(map, 3, 1);
}

// Part two is slightly more complicated - we'll iterate through a list of slopes to get our answer.
int partTwo(const std::vector<std::vector<char>>& map) {
    auto slopes = std::list<std::pair<int, int>>{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

    // for some reason, this is returning an incorrect value. however, manual multiplication of the results is correct.
    // so, need to investigate this futher...maybe int isn't adequate?
    int result = 1;
    for (auto& i : slopes) {
        result *= countTrees(map, i.first, i.second);
    }

    return result;
}

int main() {
    std::ifstream in("../Inputs/Day_03.txt");
    std::string buf;
    std::vector<std::vector<char>> map;
    while (std::getline(in, buf)) {
        std::vector<char> bufc;
        for (char& c : buf) {
            bufc.push_back(c);
        }

        map.emplace_back(std::move(bufc));
    }

    std::cout << "Part One: " << partOne(map) << std::endl;
    std::cout << "Part Two: " << partTwo(map) << std::endl;

    return 0;
}
