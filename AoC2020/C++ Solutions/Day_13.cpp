#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <sstream>

// Useful for part one...not at all for part two!
struct Bus {
    Bus(int input) { id = input; }
    int id, stepCount, earliestTime, diff;
};

int partOne() {
    std::ifstream in("../Inputs/Day_13.txt");
    std::string worker;
    std::getline(in, worker);
    auto earliestTime = std::stoi(worker);

    std::vector<Bus> busses; // id, #steps, earliest time, diff

    while(getline(in, worker, ',')) { 
        if (worker != "x") {
            busses.emplace_back(Bus(std::stoi(worker)));
        }
    }

    in.close();

    for (auto& b : busses) {
        while (b.earliestTime < earliestTime) {
            b.stepCount++;
            b.earliestTime += b.id;
        }

        b.diff = b.earliestTime - earliestTime;
    }

    for (int i = 0; i < busses.size(); i++) {
        while (busses.at(i).earliestTime < earliestTime) {
            busses.at(i).stepCount++;
            busses.at(i).earliestTime += busses.at(i).id;
        }

        busses.at(i).diff = busses.at(i).earliestTime - earliestTime;
    }

    int minWait = 999;
    int minID = 0;

    for (auto& b : busses) {
        if (b.diff < minWait) {
            minWait = b.diff;
            minID = b.id;
        }
    }

    return minWait * minID;
}

// This is a helper for the Chinese Remainder Theorem
uint64_t findInverse(uint64_t a, uint64_t b) {
    uint64_t b0 = b;
    uint64_t x0 = 0;
    uint64_t x1 = 1;

    if (b == 1) {
        return 1;
    }

    while (a > 1) {
        uint64_t q = a / b;
        uint64_t mod = a % b;
        a = b;
        b = mod;

        uint64_t xqx = x1 - q * x0;
        x1 = x0;
        x0 = xqx;
    }

    if (x1 < 0) {
        x1 += b0;
    }

    return x1;
};

// To-do: learn more about the Chinese Remainder Theorem
uint64_t findRemainder(const std::vector<int>& a, const std::vector<int>& n) {
    uint64_t M = 1;

    for (auto& i : n) { 
        M *= i;
    }

    uint64_t sum = 0;

    for (int i = 0; i < n.size(); i++) {
        uint64_t Mi = M / n.at(i);
        sum += a.at(i) * Mi * findInverse(Mi % n.at(i), n.at(i));
    }

    return sum % M;
}

uint64_t partTwo() {
    // Part Two: this is not my solution, but rather that of https://github.com/memoriesadrift
    // It is my intention to study and learn from the solution
    std::ifstream in("../Inputs/Day_13.txt");
    std::string worker;
    uint64_t earliestTime;
    int offset = 0;
    std::vector<int> busIDs;
    std::vector<int> offsets;

    std::getline(in, worker); // don't need this for anything, so just carry on

    // sstream is most efficient here
    while(getline(in, worker)) { 
        std::stringstream ss(worker);

        for (int id; ss >> id;) {
            busIDs.emplace_back(id);

            if (busIDs.size() == 1) {
                offsets.emplace_back(offset);
            } else {
                offsets.emplace_back(id - offset);
            }

            while (ss.peek() == ',' || ss.peek() == 'x') {
                ss.ignore();
                if (ss.peek() == 'x') {
                    continue;
                }
                offset++;
            }
        }
    }
    in.close();

    return findRemainder(offsets, busIDs);
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;

    return 0;
}