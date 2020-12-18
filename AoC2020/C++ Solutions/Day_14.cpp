#include "common.h"
#include <unordered_map>

struct mask_t {
    uint64_t ones;
    uint64_t zeroes;
    uint64_t xs;
    std::string rawString;
};

struct instruction_t {
    enum type_t { 
        Mask,
        Memory
    };

    type_t type;
    uint64_t value{0};
    uint64_t address{0};
    mask_t mask{};
};

struct computer_t {
    std::unordered_map<uint64_t, uint64_t> memory{};
    mask_t mask{};

    void driverV1(const std::vector<instruction_t>& instructions) {
        for (auto& i : instructions) {
            switch (i.type) {
                case instruction_t::Mask:
                    mask = i.mask;
                    break;

                case instruction_t::Memory:
                    const auto zeroed = i.value & (~mask.zeroes);
                    const auto masked = zeroed | mask.ones;
                    memory[i.address] = masked;
                    break;
            }
        }
    }

    std::vector<uint64_t> decodeAddresses(uint64_t address, const std::string& mask) {
        std::vector<uint64_t> results{address};

        for (size_t i = 0; i < mask.size(); i++) {
            auto bit = mask[mask.size() - i - 1];
            if (bit == 'X') {
                size_t m = results.size();
                for (size_t j = 0; j < m; j++) {
                    auto& current = results[j];
                    results.push_back(current ^ (1ULL << i));
                }
            }
            else if (bit == '1') {
                size_t m = results.size();
                for (size_t j = 0; j < m; j++) {
                    results[j] |= (1ULL << i);
                }
            }
        }

        return results;
    }

    void driverV2(const std::vector<instruction_t>& instructions) {
        // this is going to be tough
        for (auto& i : instructions) {
            switch (i.type) {
                case instruction_t::Mask:
                    mask = i.mask;
                    break;

                case instruction_t::Memory:
                    for (auto& a : decodeAddresses(i.address, i.mask.rawString)) {
                        memory[a] = i.value;
                    }
                    break;
            }
        }
    }
};

uint64_t partOne(const std::vector<instruction_t> instructions) {
    computer_t comp;
    comp.driverV1(std::move(instructions));

    uint64_t counter{0};
    for (auto& [address, value] : comp.memory) {
        counter += value;
    }

    return counter;
}

uint64_t partTwo(const std::vector<instruction_t> instructions) {
    computer_t comp;
    comp.driverV2(std::move(instructions));

    uint64_t counter{0};
    for (auto& [address, value] : comp.memory) {
        counter += value;
    }

    return counter;
}

int main() {
    std::ifstream in("../Inputs/Day_14.txt");
    std::string line;
    std::vector<instruction_t> instructions;
    while (std::getline(in, line)) {
        instructions.emplace_back();
        auto& instruction = instructions.back();
        switch (line[1]) {
            case 'a': {
                instruction.type = instruction_t::Mask;
                auto* maskStr = line.data() + 7;
                instruction.mask.rawString = maskStr;
                for (int i = 35; i >= 0; i--) {
                    switch (maskStr[i]) {
                        case '1':
                            instruction.mask.ones |= 1ull << (35 - i);
                            break;

                        case '0':
                            instruction.mask.zeroes |= 1ull << (35 - i);
                            break;

                        case 'X':
                            instruction.mask.xs |= 1ull << (35 - i);
                            break;
                    }
                }
                break;
            }
            case 'e': {
                instruction.type = instruction_t::Memory;
                auto s = split(line, '=');
                instruction.address = std::atoi(line.data() + 4);
                instruction.value = std::atoi(s.back().data() + 1);
                break;
            }
        }
    }

    std::cout << "Part One: " << partOne(instructions) << std::endl;
    std::cout << "Part Two: " << partTwo(instructions) << std::endl;
}