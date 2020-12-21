#include "common.h"
#include <algorithm>

std::vector<std::string> input;
uint64_t numCycles{6};
uint64_t width, height, depth;

uint64_t countNeighbors(const std::vector<std::vector<std::vector<bool>>>& grid, const uint64_t& x, const uint64_t& y, const uint64_t& z) {
    uint64_t count{0};

    for (uint64_t iz = std::max(0ull, z-1); iz < std::min(z+2, depth); iz++) {
        for (uint64_t iy = std::max(0ull, y-1); iy < std::min(y+2, height); iy++) {
            for (uint64_t ix = std::max(0ull, x-1); ix < std::min(x+2, width); ix++) {
                if (grid[iz][iy][ix]) {
                    count++;
                }
            }
        }
    }

    if (grid[z][y][x]) {
        count--;
    }
    return count;
}

uint64_t partOne() {
    width = (2 * numCycles) + input[0].size();
    height = (2 * numCycles) + input.size();
    depth = (2 * numCycles) + 1;

    std::vector<std::vector<std::vector<bool>>> grid (
        depth, std::vector<std::vector<bool>> (
            height, std::vector<bool> (
                width, false )));

    for (uint64_t y = 0; y < input.size(); y++) {
        for (uint64_t x = 0; x < input[y].size(); x++) {
            grid[numCycles][numCycles + y][numCycles + x] = input[y][x] == '#';
        }
    }

    uint64_t lastCount;
    for (uint64_t c = 0; c < numCycles; c++) {
        lastCount = 0;
        auto newGrid = grid;
        for (uint64_t z = 0; z < depth; z++) {
            for (uint64_t y = 0; y < height; y++) {
                for (uint64_t x = 0; x < width; x++) {
                    uint64_t neighbors = countNeighbors(grid, x, y, z);
                    if (grid[z][y][x]) {
                        newGrid[z][y][x] = (neighbors == 2) || (neighbors == 3);
                    } else {
                        newGrid[z][y][x] = (neighbors == 3);
                    }

                    if (newGrid[z][y][x]) {
                        lastCount++;
                    }
                }
            }
        }

        grid = std::move(newGrid);
    }

    return lastCount;
}

int main() {
    std::ifstream in("../Inputs/Day_17.txt");
    std::string worker;
    while(std::getline(in, worker)) {
        input.emplace_back(worker);
    }

    std::cout << "Part One: " << partOne() << std::endl;
    //std::cout << "Part Two: " << partTwo() << std::endl;

    return 0;
}
