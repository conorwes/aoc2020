#include "common.h"

enum class Cell {
    Floor,
    Empty,
    Occupied
};

struct Map {
    std::vector<std::vector<Cell>> rows;
    std::vector<std::vector<std::vector<std::pair<int, int>>>> deps;
    int tolerance = 0;

    // function to count seats in use
    int countOccupied(int row, int col) const {
        int count = 0;
        for (auto [r, c] : deps[row][col]) {
            if (rows[r][c] == Cell::Occupied) {
                count++;
            }
        }

        return count;
    }

    // function to process the next seat
    Cell processNext(int row, int col) const {
        Cell currentCell = rows[row][col];
        switch (currentCell) {
            case Cell::Floor:
                return Cell::Floor;

            case Cell::Empty:
                return countOccupied(row, col) == 0 ? Cell::Occupied : Cell::Empty;

            case Cell::Occupied:
                return countOccupied(row, col) >= 4 + tolerance ? Cell::Empty : Cell::Occupied;
        }

        return Cell::Empty;
    }

    // function to step through the row
    void takeNextStep(std::vector<std::vector<Cell>>& result) const {
        for (int row = 0; row < rows.size(); row++) {
            for (int col = 0; col < rows[row].size(); col++) {
                result[row][col] = processNext(row, col);
            }
        }
    }

    // function to count all occupied seats
    int countAllOccupied() const {
        int count = 0;
        for (int i = 0; i < rows.size(); i++) {
            for (int j = 0; j < rows[i].size(); j++) {
                if (rows[i].at(j) == Cell::Occupied) {
                    count++;
                }
            }
        }

        return count;
    }

    // driver
    int run() {
        std::vector<std::vector<Cell>> next = rows;
        while (true) {
            takeNextStep(next);
            if (rows == next) {
                return countAllOccupied();
            }
            std::swap(rows, next);
        }
    }
};

int partOne(const Map& map) {
    Map worker = map;
    worker.deps.resize(map.rows.size());

    for (int row = 0; row < map.rows.size(); row++) {
        const auto& rrow = worker.rows[row];
        auto& rdep = worker.deps[row];
        rdep.resize(rrow.size());
        for (int col = 0; col < rrow.size(); col++) {
            auto& deps = rdep[col];
            for (int nrow : {row - 1, row, row + 1}) {
                for (int ncol : {col - 1, col, col + 1}) {
                    if (nrow != row || ncol != col) {
                        try {
                            if (map.rows.at(nrow).at(ncol) != Cell::Floor) {
                                deps.emplace_back(std::make_pair(nrow, ncol));
                            }
                        } catch (const std::out_of_range&) {

                        }
                    }
                }
            }
        }
    }
    return worker.run();
}

int partTwo(const Map& map) {
    Map worker = map;
    worker.deps.resize(map.rows.size());
    worker.tolerance = 1;

    for (int row = 0; row < map.rows.size(); row++) {
        const auto& rrow = worker.rows[row];
        auto& rdep = worker.deps[row];
        rdep.resize(rrow.size());
        for (int col = 0; col < rrow.size(); col++) {
            if (rrow[col] == Cell::Floor) {
                continue;
            }
            auto& deps = rdep[col];
            for (int drow : {-1, 0, 1}) {
                for (int dcol : {-1, 0, 1}) {
                    if (drow || dcol) {
                        int lrow = row;
                        int lcol = col;
                        try {
                            while (true) {
                                lrow += drow;
                                lcol += dcol;
                                Cell currentCell = map.rows.at(lrow).at(lcol);
                                if (currentCell == Cell::Floor) {
                                    continue;
                                }
                                deps.push_back(std::make_pair(lrow, lcol));
                                break;
                            }
                        } catch (const std::out_of_range&) {

                        }
                    }
                }
            }
        }
    }

    return worker.run();
}

int main() {
    std::ifstream in("../Inputs/Day_11.txt");
    std::string row;
    std::vector<std::string> grid;
    while (std::getline(in, row)) {
        grid.emplace_back(row);
    }

    Map map;
    std::vector<Cell> worker;
    for (auto& r : grid) {
        for (auto& c : r) {
            if (c == 'L') {
                worker.emplace_back(Cell::Empty);
            } else if (c == '.') {
                worker.emplace_back(Cell::Floor);
            }
            else {
                worker.emplace_back(Cell::Occupied);
            }
        }

        map.rows.emplace_back(std::move(worker));
        worker.clear();
    }

    std::cout << "Part One: " << partOne(map) << std::endl;
    std::cout << "Part Two: " << partTwo(map) << std::endl;

    return 0;
}
