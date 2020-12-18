#include "common.h"

// 0 - North
// 90 - East
// 180 - South
// 270 - West

struct Ferry {
    int facing = 90; // East
    std::pair<int, int> pos; // <N+/S-, E+/W->

    void doTask(char t, int value) {
        switch (t) {
            case 'N':
                pos.first += value;
                break;

            case 'S':
                pos.first -= value;
                break;

            case 'E':
                pos.second += value;
                break;

            case 'W':
                pos.second -= value;
                break;

            case 'R':
                setFacing(facing, value);
                break;

            case 'L':
                setFacing(facing, -1 * value);
                break;

            case 'F':
                switch (facing / 90) {
                    case 0:
                        pos.first += value;
                        break;

                    case 1:
                        pos.second += value;
                        break;

                    case 2:
                        pos.first -= value;
                        break;

                    case 3:
                        pos.second -= value;
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

    void setFacing(int& facing, int value) {
        facing += value;
        if (facing == 360) {
            facing = 0;
        }

        while (facing > 360) { 
            facing -= 360;
        }

        while (facing < 0) {
            facing += 360;
        }
    }

    void driver(const std::vector<std::pair<char, int>> directions) {
        for (auto& d : directions) {
            doTask(d.first, d.second);
        }
    }
};

struct Waypoint {
    std::pair<int, int> pos{1, -10};
    std::pair<int, int> ferryPos{0, 0};

    void doTask(char t, int value) {
        switch (t) {
            case 'N':
                pos.first += value;
                break;

            case 'S':
                pos.first -= value;
                break;

            case 'E':
                pos.second -= value;
                break;

            case 'W':
                pos.second += value;
                break;

            case 'R':
                rotateWaypoint(value);
                break;

            case 'L':
                rotateWaypoint(-1 * value);
                break;

            case 'F':
                ferryPos.first += value * pos.first;
                ferryPos.second += value * pos.second;
                break;

            default:
                // do nothing;
                break;
        }
    }

    void rotateWaypoint(int i) {
        // R rotation
        if (i > 0){
            while(i)
            {
                int temp = pos.first;
                pos.first = pos.second;
                if(temp == 0) { pos.second = temp; }
                else { pos.second = -1 * temp; }
                i-= 90;
            }
        } else 
        {
            i = i * -1;
            while(i)
            {
                int temp = pos.second;
                pos.second = pos.first;
                if(temp == 0) { pos.first = temp; }
                else { pos.first = -1 * temp; }
                i-= 90;
            }
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

    return manhattanDistance(f.pos.first, f.pos.second, 0, 0);
}

int partTwo(const std::vector<std::pair<char, int>>& directions) {
    Waypoint w;
    w.driver(std::move(directions));

    return manhattanDistance(w.ferryPos.first, w.ferryPos.second, 0, 0);
}

int main() {
    std::ifstream in("../Inputs/Day_12.txt");
    std::string row;
    std::vector<std::pair<char, int>> directions;
    while (std::getline(in, row)) {
        if (row != "") {
            directions.emplace_back(std::make_pair(row.at(0), std::stoi(row.substr(1))));
        }
    }

    std::cout << "Part One: " << partOne(std::move(directions)) << std::endl;
    std::cout << "Part Two: " << partTwo(std::move(directions)) << std::endl;

    return 0;
}