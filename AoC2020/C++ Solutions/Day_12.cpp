
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Ferry {
    int facing = 1;
    int posX = 0;
    int posY = 0;

    void doTask(char t, int value) {
        switch (t) {
            case 'N':
                posY += value;
                break;

            case 'S':
                posY -= value;
                break;

            case 'E':
                posX += value;
                break;

            case 'W':
                posX -= value;
                break;

            case 'R':
                facing += value / 90;
                break;

            case 'L':
                facing -= value / 90;
                break;

            case 'F':
                switch (facing & 4) {
                    case 0:
                        posY += value;
                        break;

                    case 1:
                        posX += value;
                        break;

                    case 2:
                        posY -= value;
                        break;

                    case 3:
                        posX -= value;
                        break;

                    default:
                        // do nothing;
                        break;
                }
                break;

            default:
                // do nothing;
                break;
        }
    }

    void driver(const std::vector<std::pair<char, int>> directions) {
        for (auto& d : directions) {
            doTask(d.first, d.second);
        }
    }
};

int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

int partOne(const std::vector<std::pair<char, int>>& directions) {
    Ferry f;
    f.driver(std::move(directions));

    return manhattanDistance(f.posX, f.posY, 0, 0);
}

int main() {
    std::ifstream in("../Inputs/Day_12.txt");
    std::string row;
    std::vector<std::pair<char, int>> directions;
    while (std::getline(in, row)) {
        if (row != "") {
            directions.emplace_back(std::make_pair(row.at(0), std::stoi(row.data() + 1)));
        }
    }

    std::cout << "Part One: " << partOne(directions) << std::endl;
    //std::cout << "Part Two: " << partTwo(directions) << std::endl;

    return 0;
}