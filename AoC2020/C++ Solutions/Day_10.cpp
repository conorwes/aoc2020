
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

// Part one is pretty straightforward - just iterate through all pairs and count the difference
uint64_t partOne(const std::vector<int>& adapters) {
    int countOneDiff = 0;
    int countThreeDiff = 0;

    auto diffPair = [&countOneDiff, &countThreeDiff](int lower, int upper) {
        int diff = upper - lower;

        if (diff == 1) {
            countOneDiff++;
        }
        else if (diff == 3) {
            countThreeDiff++;
        }
    };

    for (int i = 0; i < adapters.size() - 1; i++) {
        diffPair(adapters[i], adapters[i + 1]);
    }

    return countOneDiff * countThreeDiff;
}

// Part two was a nightmare that ultimately turned out to be user error - I was having it return int, when we all know the number is massive.
// I tried 3 approaches, with this one being the final one before I realized I'm a moron.
uintmax_t partTwo(std::vector<int>& adapters) {
    // this approach takes advantage of memoization - by summing as we go, we avoid having to recursively compute chains
    std::unordered_map<std::uintmax_t, std::uintmax_t> counts{{0, 1}};
    for (auto& a : adapters) {
        /*std::cout << a << ": {" << counts[a - 1] << ", " << counts[a - 2] << ", " << counts[a - 3] << "}" << std::endl;*/ //uncomment to debug
        counts[a] += counts[a - 1] + counts[a - 2] + counts[a - 3];
    }

    return counts[adapters.back()];
}

int main() {
    std::ifstream in("../Inputs/Day_10.txt");
    std::string line;
    std::vector<int> adapters;

    // include outlet
    adapters.emplace_back(0);

    while (std::getline(in, line)) {
        adapters.emplace_back(std::stoi(line));
    }

    // include device
    adapters.emplace_back(3 + *std::max_element(adapters.begin(), adapters.end()));

    std::sort(adapters.begin(), adapters.end());

    std::cout << "Part One: " << partOne(adapters) << std::endl;
    std::cout << "Part Two: " << partTwo(adapters) << std::endl;

    return 0;
}