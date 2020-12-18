#include "common.h"

using task_t = std::pair<std::string, std::string>;

std::pair<bool, int> driver(const std::vector<task_t>& instructions) {
    int sum = 0;
    int counter = 0;
    bool completed = false;
    std::vector<bool> visited(instructions.size(), false);

    do {
        // First, check if we're done
        if (counter == instructions.size()) {
            completed = true;
            break;
        }

        auto task = instructions.at(counter);

        // if already visited, we've found our infinite loop - so break
        if (visited.at(counter)) {
            break;
        }

        visited.at(counter) = true;

        if (task.first == "acc") {
            sum += std::stoi(task.second);
            counter++;
        } else if (task.first == "jmp") {
            counter += std::stoi(task.second);
        } else if (task.first == "nop") {
            counter++;
        } else {
            std::cout << "Bad task" << std::endl;
            exit(1);
        }
    } while(true);
    return std::make_pair(completed, sum);
}

int partOne(const std::vector<task_t>& instructions) {
    auto [completed, sum] = driver(instructions);
    return sum;
}

int partTwo(const std::vector<task_t>& instructions) {
    auto needsChanged = [](const std::string& t) {
        return (t == "jmp" || t == "nop");
    };

    auto fixTask = [](task_t& t) {
        if (t.first == "jmp") {
            return std::string("nop");
        } else {
            return std::string("jmp");
        }
    };


    for (int i = 0; i < instructions.size(); i++) {
        if (needsChanged(instructions.at(i).first)) {
                auto newInstructions = instructions;
                newInstructions.at(i).first = fixTask(newInstructions.at(i));
                auto [completed, sum] = driver(newInstructions);
                if (completed) {
                    return sum;
                }
            }
    }
}

int main() {
    std::ifstream in("../Inputs/Day_08.txt");
    std::string line;
    std::vector<task_t> instructions;

    while (std::getline(in, line)) {
        instructions.emplace_back(std::make_pair(line.substr(0, 3), line.substr(4, line.size())));
    }

    std::cout << "Part One: " << partOne(instructions) << std::endl;
    std::cout << "Part Two: " << partTwo(instructions) << std::endl;

    return 0;
}