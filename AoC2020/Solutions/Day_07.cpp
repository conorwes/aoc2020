
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Bag {
public:
    Bag(std::string&& type) { description = type;
    }

    std::string getDescription() const {
        return description;
    }

    void addChildBag(int count, const Bag& bag) {
        childBags.emplace_back(std::make_pair(count, bag));
    }

    std::vector<std::pair<int, Bag>> getChildBags() const {
        return childBags;
    }

    bool containsBagType(std::string&& bagType) const {
        for(auto& cb : childBags) {
            if (cb.second.getDescription() == bagType || 
                cb.second.containsBagType(std::move(bagType))) {
                return true;
            }
        }
    }

    void reportContents() const {
        std::cout << getDescription() << ": ";
        for (auto& cb : childBags) {
            std::cout << cb.second.getDescription() << "{ ";
            for (auto& cbb : cb.second.getChildBags()) {
                std::cout << cbb.second.getDescription() << " ";
            }
            std::cout << "} ";
        }

        std::cout << std::endl << std::endl;
    }

private:

    std::string description;
    std::vector<std::pair<int, Bag>> childBags;
};

std::pair<std::string, std::vector<std::pair<int, std::string>>> parseRule(std::string&& line) {
    
    auto cleanDescription = [](std::string&& description) {
        return description.erase(description.find("bag"), std::string::npos);
    };
    
    std::string parentBag;
    std::vector<std::pair<int, std::string>> childBags;
    int count = 0;
    std::string description;

    std::string delimiter = " contain ";
    int length = line.find(delimiter);
    parentBag = cleanDescription(std::move(line.substr(0, length)));
    line.erase(0, length + delimiter.size());

    // this is a _mess_. do this much more cleanly
    delimiter = ", ";
    if (line.find(',') != std::string::npos)
    { 
        while (length != std::string::npos) {
            length = line.find(" ");
            count = std::stoi(line.substr(0, length));
            line.erase(0, length + 1);
            length = line.find(delimiter);
            description = cleanDescription(std::move(line.substr(0, length)));
            line.erase(0, length + 2);
            length = line.find(delimiter);

            childBags.emplace_back(std::make_pair(count, description));
        }

        length = line.find(" ");
        count = std::stoi(line.substr(0, length));
        line.erase(0, length + 1);
        length = line.find(".");
        description = cleanDescription(std::move(line.substr(0, length)));
        line.erase(0, length + 1);

        childBags.emplace_back(std::make_pair(count, description));
    }
    else if (line.find("no other bags") != std::string::npos)
    {
        childBags.emplace_back(std::make_pair(0, "null"));
    }
    else {
        length = line.find(" ");
        count = std::stoi(line.substr(0, length));
        line.erase(0, length + 1);
        length = line.find(".");
        description = cleanDescription(std::move(line.substr(0, length)));
        line.erase(0, length + 1);

        childBags.emplace_back(std::make_pair(count, description));
    }

    return std::make_pair(parentBag, childBags);
}

void fillBags(const std::pair<std::string, std::vector<std::pair<int, std::string>>>& rule, std::vector<Bag>& bagTypes) {
    for (int i = 0; i < bagTypes.size(); i++) {
        if (bagTypes.at(i).getDescription() == rule.first) {
            for (auto& cb : rule.second) {
                for (auto& b : bagTypes) {
                    if (b.getDescription() == cb.second) {
                        bagTypes.at(i).addChildBag(cb.first, b);
                    }
                }
            }
        }
    }
}

int partOne(const std::vector<std::pair<std::string, std::vector<std::pair<int, std::string>>>>& rules) {
    std::vector<std::string> containerBags;

    // first get lowest level: bags which explicitly state they can contain shiny gold bags
    for (auto& r : rules) {
        for (auto& c : r.second) {
            if (c.second.find("shiny gold") != std::string::npos) {
                containerBags.emplace_back(r.first);
            }
        }
    }

    return containerBags.size();
}

int main() {
    std::ifstream in("../Inputs/Day_07.txt");
    std::string line;
    std::vector<std::pair<std::string, std::vector<std::pair<int, std::string>>>> rules; // gross

    while (std::getline(in, line)) {
        rules.emplace_back(parseRule(std::move(line)));
    }

    std::vector<Bag> bagTypes;
    for (auto& r : rules) {
        bagTypes.emplace_back(std::move(r.first));
    }

    //bagTypes[0].reportContents();

    for (auto& r: rules) {
        fillBags(r, bagTypes);
    }

    auto bag = bagTypes[0];
    bag.reportContents();

    /*for (auto& b: bagTypes) {
        b.reportContents();
    }*/

    //std::cout << "Part One: " << partOne(rules) << std::endl;
    //std::cout << "Part Two: " << partTwo(vec) << std::endl;

    return 0;
}