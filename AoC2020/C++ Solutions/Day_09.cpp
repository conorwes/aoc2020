
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

bool checkCombos(std::deque<uint64_t>& input, uint64_t goal) {
    std::vector<bool> mask(input.size());
    std::fill(mask.end() - 2, mask.end(), true);

    do {
        uint64_t temp = 0;
        for (int i = 0; i < input.size(); i++) {
            if (mask[i]) {
                temp += input[i];
            }
        }
        if (temp == goal) {
            return true;
        }
    } while (std::next_permutation(mask.begin(), mask.end()));
    return false;
}

uint64_t partOne(const std::vector<uint64_t>& input) {
    std::deque<uint64_t> testRange(input.begin(), input.begin() + 25);
    for (int i = 25; i < input.size(); i++) {
        uint64_t goal = input[i];
        if (!checkCombos(testRange, goal)) {
            return goal;
        }

        testRange.push_back(input[i]);
        testRange.pop_front();
    }

    return 0;
}

uint64_t partTwo(const std::vector<uint64_t>& input, uint64_t goal) {
    for (int i = 0; i < input.size(); i++) {
        int index = 0;
        uint64_t sum = 0;

        do {
            sum += input[i + index];
            if (sum == goal) {
                auto begin = input.begin() + i;
                auto end = input.begin() + i + index;
                return *std::min_element(begin, end) + *std::max_element(begin, end);
            }
            index++;
        } while ((i + index) < input.size() && !(sum > goal));
    }
    return 0;
}

int main() {
    std::ifstream in("../Inputs/Day_09.txt");
    std::string line;
    std::vector<uint64_t> input;

    while (std::getline(in, line)) {
        char* c = &line[0];
        input.emplace_back(strtoull(c, NULL, 0));
    }

    std::cout << "Part One: " << partOne(input) << std::endl;
    std::cout << "Part Two: " << partTwo(input, (uint64_t)542529149) << std::endl;

    return 0;
}