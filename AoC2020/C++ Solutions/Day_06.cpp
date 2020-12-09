
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

// Part one: sum up all 'yes' answers
int partOne(const std::vector<std::vector<std::string>>& groups) {
    int sum = 0;
    std::unordered_set<char> answers;

    /*std::ofstream myFile;
    myFile.open("../Debug/Day06_C++_Inputs.txt");*/

    // We just need to accumulate answers and sum them
    for (auto& group : groups) {
        for (auto& line : group) {
            answers.insert(line.begin(), line.end());
        }

        /*for (auto& c: answers) {
            myFile << c;
        }
        myFile << " " << answers.size() << " " << sum << std::endl;*/
        sum += answers.size();
        answers.clear();
    }

    //myFile.close();

    return sum;
}

// Part two: sum up all answers where each member of the group said 'yes'
int partTwo(const std::vector<std::vector<std::string>>& groups) {
    int sum = 0;
    std::string seen;

    // We just need to iterate through the first member's answers and check against the rest of the group,
    // removing any characters which aren't found in the others' answers
    for (auto& group : groups) {
        seen = group[0];
        for (int i = 1; i < group.size(); i++) {
            seen.erase(
                std::remove_if(seen.begin(), seen.end(), 
                    [&group, &i](char c) { return group[i].find(c) == std::string::npos; }
                ),
                seen.end()
            );
        }
        sum += seen.size();
    }

    return sum;
}

int main() {
    std::ifstream in("../Inputs/Day_06.txt");
    std::string line;
    std::vector<std::vector<std::string>> groups;
    std::vector<std::string> forms;

    while (std::getline(in, line)) {
        if (line != "") {
            forms.emplace_back(line);
        }
        else {
            groups.emplace_back(std::move(forms));
            forms = {};
        }
    }

    groups.emplace_back(std::move(forms));

    std::cout << "Part One: " << partOne(groups) << std::endl;
    std::cout << "Part Two: " << partTwo(groups) << std::endl;

    return 0;
}