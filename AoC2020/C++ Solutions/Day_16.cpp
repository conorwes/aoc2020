#include "common.h"
#include <algorithm>
#include <unordered_set>

struct rule_t {
    std::string name;
    std::vector<std::pair<int, int>> ranges;
    int fieldIndex;

    bool isValid(int value) const {
        bool valid = ((value >= ranges[0].first && value <= ranges[0].second) ||
                      (value >= ranges[1].first && value <= ranges[1].second));
        return valid;
    }
};

std::vector<rule_t> rules;

struct ticket_t {
    std::vector<int> values;

    int countInvalid() const {
        int counter{0};

        for (auto& v : values) {
            auto check = [&v](const rule_t& rule) {
                return rule.isValid(v);
            };

            if (!std::any_of(rules.begin(), rules.end(), std::move(check))) {
                counter += v;
            }
        }

        return counter;
    }
};

std::vector<ticket_t> tickets;
std::vector<ticket_t> validTickets;

using possible_fields_t = std::vector<std::unordered_set<int>>;

// method to collect possible field indices for each ticket field
possible_fields_t collectPossibleFields() {
    possible_fields_t possibleFields;
    possibleFields.resize(validTickets.front().values.size());

    for (int i = 0; i < validTickets.front().values.size(); i++) {
        for (int j = 0; j < rules.size(); j++) {
            auto check = [&i, &j](const ticket_t ticket) {
                return rules[j].isValid(ticket.values.at(i));
            };

            // if field is valid for all tickets at this index, we have a winner
            if (std::all_of(validTickets.begin(), validTickets.end(), std::move(check))) {
                possibleFields[i].insert(j);
            }
        }
    }
    return possibleFields;
}

// once we've collected all fields, we can deduce the proper indices
void findCorrectFields(possible_fields_t& possibleFields) {
    auto sizeCheck = [](const std::unordered_set<int>& set) -> bool {
        return set.size();
    };

    // loop until we can no longer find a set that contains more than 0 elements
    while (std::any_of(possibleFields.begin(), possibleFields.end(), std::move(sizeCheck))) {
        for (int i = 0; i < possibleFields.size(); i++) {
            // found a winner!
            if (possibleFields.at(i).size() == 1) {
                int fieldIndex = *possibleFields.at(i).begin();
                rules[fieldIndex].fieldIndex = i;

                // now clean up other possible sets
                for (auto& fieldsSet : possibleFields) {
                    fieldsSet.erase(fieldIndex);
                }
            }
        }
    }
}

int partOne() {
    int counter{0};

    for (int i = 1; i < tickets.size(); i++) {
        int count = tickets.at(i).countInvalid();
        counter += count;

        // for part two, collect valid tickets here
        if (count == 0) { 
            validTickets.emplace_back(tickets.at(i));
        }
    }

    return counter;
}

uint64_t partTwo() {
    possible_fields_t possibleFields = collectPossibleFields();
    findCorrectFields(possibleFields);
    uint64_t result{1};

    // we can be lazy here since rows 0-5 are the departure rules
    for (int i = 0; i < 6; i++) {
        result *= tickets.at(0).values.at(rules.at(i).fieldIndex);
    }

    return result;
}

int main() {
    std::ifstream in("../Inputs/Day_16.txt");
    std::string worker;

    while (std::getline(in, worker)) {
        if (worker != "") {
            if (std::isalpha(worker[0]) && worker[0] != 'y' && worker[0] != 'n') {
                // this is a rule
                rules.emplace_back();

                // first get name
                int len = worker.find(':');
                rules.back().name = worker.substr(0, len);

                // then fill bounds
                worker.erase(0, len + 2);
                rules.back().ranges.emplace_back();
                len = worker.find('-');
                rules.back().ranges.back() = std::make_pair(std::stoi(worker.substr(0, len)), 
                                                            std::stoi(worker.substr(len + 1, worker.find(' '))));

                worker.erase(0, worker.find(' ') + 3);
                len = worker.find('-');
                rules.back().ranges.emplace_back();
                rules.back().ranges.back() = std::make_pair(std::stoi(worker.substr(0, len)), 
                                                            std::stoi(worker.substr(len + 1)));
            }
            else if (worker[0] == 'y' || worker[0] == 'n') {
                // skip this line
                continue;
                
            }
            else {
                tickets.emplace_back();
                auto values = split(worker, ',');
                for (auto& v : values) {
                    tickets.back().values.emplace_back(std::stoi(v));
                }
            }
        }
    }

    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;

    return 0;
}