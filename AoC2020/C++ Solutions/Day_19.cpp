#include "common.h"
#include <unordered_map>

using namespace std;
using ll = long long;

vector<string> input;
unordered_map<int, vector<vector<int>>> rules; // we'll treat char as int

int main() {
    ifstream in("../Inputs/Day_19.txt");
    string worker;
    vector<vector<int>> values;
    while(getline(in, worker)) {
        if(worker == "") {
            continue;
        } else if (!isalpha(worker[0])) {
            auto tokens = split(trim(worker), ':');
            
            // need to evaluate rules to determine what we've got
            if (tokens[1].find('|') != string::npos) {
                //vector of vector<int>
                size_t pipePos = tokens[1].find('|');
                values.resize(2);
                for(auto& i : split(trim(tokens[1].substr(0, pipePos - 1)), ' ')) {
                    values[0].emplace_back(stoi(i));
                }

                for (auto& i : split(trim(tokens[1].substr(pipePos + 1)), ' ')) {
                    values[1].emplace_back(stoi(i));
                }
            } else if (tokens[1].find("\"") != string::npos) {
                // char
                values.resize(1);
                values[0][0] = (trim(tokens[1])[1]);
            } else {
                values.resize(1);
                for(auto& i : split(trim(tokens[1]), ' ')) {
                    values[0].emplace_back(stoi(i));
                    std::cout << stoi(i) << " ";
                }
            }
            rules[stoi(tokens[0])] = values;
        } else {
            input.emplace_back(worker);
        }
    }

    return 0;
}