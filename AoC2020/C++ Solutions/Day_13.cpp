#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Bus {
    Bus(int input) { id = input; }
    int id, stepCount, earliestTime, diff;
};

int partOne(const std::vector<Bus>& busses, const int earliestTime) {
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

int main() {
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

    std::cout << "Part One: " << partOne(std::move(busses), earliestTime) << std::endl;
    //std::cout << "Part Two: " << partTwo(std::move(directions)) << std::endl;*/

    return 0;
}