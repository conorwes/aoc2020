
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <deque>
#include <unordered_set>
#include <regex> // after wasting several hours trying to get a parser working, I'm going to go with regex

// Define types for convenience:
using contained_t = std::unordered_map<std::string, std::unordered_set<std::string>>; // Type for bags which contain this bag
using contains_t = std::unordered_map<std::string, std::unordered_map<std::string, int>>; // Type for bags which are contained by this bag

// Build contained and contains using regex
void parseRules(std::vector<std::string> rules, contained_t& contained, contains_t& contains) {
    // Credit for these regex patterns goes to https://github.com/Kazhuu:
    std::regex parentPattern(R"((\w+ \w+) bags contain)");
    std::regex childPattern(R"(,? (\d+) (\w+ \w+) bags?)");
    
    for (auto&r : rules) {
        std::smatch parentMatch;
        std::regex_search(r, parentMatch, parentPattern);

        contains.emplace(parentMatch[1], std::unordered_map<std::string, int>());

        auto start = std::sregex_iterator(r.begin(), r.end(), childPattern);
        auto end = std::sregex_iterator();

        for (std::sregex_iterator i = start; i != end; i++) {
            std::smatch match = *i;

            contains[parentMatch[1]].emplace(match[2], std::stoi(match[1]));

            if (!contained.emplace(match[2], std::unordered_set<std::string>({parentMatch[1]})).second) {
                contained[match[2]].insert(parentMatch[1]);
            }
        }
    }
}

int partOne(contained_t& input) {
    std::deque<std::string> bag({"shiny gold"});
    std::unordered_set<std::string> seen({"shiny gold"});

    while (!bag.empty()) {
        std::string bagName = bag.front();
        for (auto& b : input[bagName]) {
            if (seen.insert(b).second) {
                bag.push_back(b);
            }
        }

        bag.pop_front();
    }

    return seen.size() - 1;
}

int countBags(contains_t& input, std::string bagName) {
    int bagCount = 0;
    for (auto& [bagName, count] : input[bagName]) {
        bagCount += count + count * countBags(input, bagName);
    }

    return bagCount;
}

int partTwo(contains_t& input) {
    return countBags(input, "shiny gold");
}

int main() {
    std::ifstream in("../Inputs/Day_07.txt");
    std::string line;
    std::vector<std::string> rules;

    while (std::getline(in, line)) {
        rules.emplace_back(line);
    }

    contained_t contained;
    contains_t contains;
    parseRules(rules, contained, contains);

    std::cout << "Part One: " << partOne(contained) << std::endl;
    std::cout << "Part Two: " << partTwo(contains) << std::endl;

    return 0;
}