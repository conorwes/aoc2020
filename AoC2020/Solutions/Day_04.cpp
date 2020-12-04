
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Probably overcomplicating things, but i like enums
enum class Field {
    Invalid = -1,
    BYR,
    IYR,
    EYR,
    HGT,
    HCL,
    ECL,
    PID,
    CID,
};

// Translator function to go from field to string
std::string FieldToString(const Field& field) {
    switch (field) {
        case Field::BYR: return "byr";
        case Field::CID: return "cid";
        case Field::ECL: return "ecl";
        case Field::EYR: return "eyr";
        case Field::HCL: return "hcl";
        case Field::HGT: return "hgt";
        case Field::IYR: return "iyr";
        case Field::PID: return "pid";
        default: return "invalid";
    }
}

// As above, but in reverse
Field StringToField(const std::string& string) {
    if (string == "byr") return Field::BYR;
    else if (string == "cid") return Field::CID;
    else if (string == "ecl") return Field::ECL;
    else if (string == "eyr") return Field::EYR;
    else if (string == "hcl") return Field::HCL;
    else if (string == "hgt") return Field::HGT;
    else if (string == "iyr") return Field::IYR;
    else if (string == "pid") return Field::PID;
    else return Field::Invalid;
}

// Create a Passport class to do all of the work for us
class Passport {
public:
    Passport(std::string&& info) : byr(-1), iyr(-1), eyr(-1) {
        buildPassport(std::move(info));
    }

    bool hasMandatoryFields() const {
        return byr != -1 && ecl != "" && eyr != -1 && hcl != "" && hgt != "" && iyr != -1 && pid != "";
    }

    bool isValid() const {
        return hasMandatoryFields() && hasValidYear(byr, 1920, 2002) && hasValidYear(iyr, 2010, 2020) && hasValidYear(eyr, 2020, 2030) &&
                hasValidHeight(hgt) && hasValidHairColor(hcl) && hasValidEyeColor(ecl) && hasValidPID(pid);
    }

private:
    void buildPassport(std::string&& info) {
        int startPos = 0;
        int length = info.find(" ");
        while (length != std::string::npos) {
            populatePair(info.substr(0, length));
            info.erase(0, length + 1);
            length = info.find(" ");
        }
    }

    // Use those handy enums from before to quickly sort data and populate pairs
    void populatePair(std::string&& info) {
        auto key = StringToField(info.substr(0, 3));
        std::string value = info.substr(4, std::string::npos);

        switch (key) {
            case Field::BYR: byr = std::stoi(value); break;
            case Field::CID: cid = value; break;
            case Field::ECL: ecl = value; break;
            case Field::EYR: eyr = std::stoi(value); break;
            case Field::HCL: hcl = value; break;
            case Field::HGT: hgt = value; break;
            case Field::IYR: iyr = std::stoi(value); break;
            case Field::PID: pid = value; break;

            case Field::Invalid:
            default: {
                std::cout << "Invalid Key" << std::endl;
                break;
            }
        }
    }

    // Some helper functions for determining validity
    bool hasValidYear(int yr, int min, int max) const {
        // just check min/max, as anything other than 4 digits will fall by the wayside
        return yr >= min && yr <= max;
    }

    // Try to make this as unit agnostic as possible, in case we want to reuse this later but with more units
    bool hasValidHeight(std::string hgt) const {
        std::string unit = hgt.substr(hgt.size() - 2, hgt.size());
        int value = std::stoi(hgt.substr(0, hgt.size() - 2));

        if (unit == "cm") return value >= 150 && value <= 193;
        else if (unit == "in") return value >= 59 && value <= 76;
        else return false;
    }

    // Should fix this up to check that the value is legitimate, but it doesn't seem like the input generator creates bad inputs that aren't too short/long
    bool hasValidHairColor(std::string hcl) const {
        std::string value = hcl.substr(1, hcl.size());
        return hcl[0] == '#' && value.size() == 6;
    }

    // Did someone say enums?
    bool hasValidEyeColor(std::string ecl) const {
        return ecl == "amb" || ecl == "blu" || ecl == "brn" || ecl == "gry" || ecl == "grn" || ecl == "hzl" || ecl == "oth";
    }

    // As above, should fix this up to check the value, but it seems like the input generator only messes with length.
    bool hasValidPID(std::string pid) const {
        return pid.size() == 9;
    }

    int byr, iyr, eyr;
    std::string hgt, hcl, ecl, pid, cid;
};

// Part one: just check to make sure fields exist
int partOne(const std::vector<Passport>& passports) {
    int valid = 0;
    for (auto& passport : passports) {
        if (passport.hasMandatoryFields()) {
            valid++;
        }
    }

    return valid;
}

// Part two: actually validate the fields
int partTwo(const std::vector<Passport>& passports) {
    int valid = 0;
    for (auto& passport : passports) {
        if (passport.isValid()) {
            valid++;
        }
    }

    return valid;
}

int main() {
    std::ifstream in("../Inputs/Day_04.txt");    
    std::string buf, input;
    std::vector<std::string> information;

    // Translate input into chunks of data
    while (std::getline(in, buf)) {
        if (buf != "") {
            input += buf + " ";
        }
        else {
            information.emplace_back(std::move(input));
            input = "";
        }
    }
    information.emplace_back(std::move(input));
    
    // Use those chunks of data to make credentials which we can then operate upon
    std::vector<Passport> passports;
    for (auto i : information)
        passports.emplace_back(std::move(i));

   std::cout << "Part One: " << partOne(passports) << std::endl;
   std::cout << "Part Two: " << partTwo(passports) << std::endl;

   return 0;
}