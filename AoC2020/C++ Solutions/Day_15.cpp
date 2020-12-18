#include "common.h"
#include <algorithm>
#include <map>

int partOne(const std::vector<int>& inputs) {
    std::vector<int> history = inputs;

    for (int turn = inputs.size(); turn < 2020; turn++) {
        auto currentNumber = *history.rbegin();
        auto it = find(history.rbegin() + 1, history.rend(), currentNumber);
        if (it == history.rend()) {
            history.push_back(0);
        } else {
            history.push_back(it - history.rbegin());
        }
    }

    return *history.rbegin();
}

int partTwo(const std::vector<int>& inputs) {
    std::map<int, int> history;

    for (int i = 0; i < inputs.size() - 1; i++) {
        history[inputs[i]] = i;
    }

    int prevNumber = *inputs.rbegin();

    for (int turn = inputs.size(); turn < 30000000; turn++) {
        int nextNumber = 0;
        if (history.find(prevNumber) != history.end()) {
            nextNumber = turn - history.at(prevNumber) - 1;
        }

        history[prevNumber] = turn - 1;
        prevNumber = nextNumber;
    }

    return prevNumber;
}

int main() {
    std::ifstream in("../Inputs/Day_15.txt");
    std::vector<int> inputs;
    std::string worker;
    std::getline(in, worker);

    for (auto&s : split(worker, ',')) {
        inputs.emplace_back(std::stoi(s));
    }

    std::cout << "Part One: " << partOne(inputs) << std::endl;
    std::cout << "Part Two: " << partTwo(inputs) << std::endl;
    
    return 0;
}