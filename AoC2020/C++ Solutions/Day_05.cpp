#include "common.h"
#include <tuple>
#include <cmath>
#include <map>

// Create a class to handle processing for us
class BoardingPass {
public:
    BoardingPass(std::string&& info) {
        buildBoardingPass(std::move(info));
    }

    std::tuple<int, int, int> getInfo() const {
        return std::make_tuple(row, col, id);
    }

    std::pair<int, int> getCoords() const {
        return std::make_pair(row, col);
    }

    int getID() const {
        return id;
    }

private:
    void buildBoardingPass(std::string&& info) {
        std::string rowInfo = info.substr(0, 7);
        std::string colInfo = info.substr(7, std::string::npos);

        // first, process the row
        auto worker = std::make_pair(0.0, 127.0);
        for (auto& r : rowInfo) {
            worker = performPartition(r, worker);
        }
        row = worker.first;

        // then, process the column
        worker = std::make_pair(0, 7);
        for (auto& c : colInfo) {
            worker = performPartition(c, worker);
        }
        col = worker.first;

        // finally compute the id
        id = row * 8 + col;
    }

    // function to perform one step of binary partitioning, agnostic of row/column
    std::pair<int, int> performPartition(char c, std::pair<double, double> bounds) {
        // hey, we're done!
        if (bounds.first == bounds.second) {
            return bounds;
        }

        switch(c){
            case 'F':
            case 'L':
                return std::make_pair(std::floor(bounds.first), std::floor((bounds.first + bounds.second) / 2));

            case 'R':
            case 'B':
                return std::make_pair(std::ceil((bounds.first + bounds.second) / 2), std::ceil(bounds.second));

            default:
                return bounds;
        }
    }

    int row, col, id;
};

// Part one: just want to find the largest ID
int partOne(const std::vector<BoardingPass>& passes) {
    int maxID = 0;

    for (auto& p : passes) {
        if (p.getID() > maxID) {
            maxID = p.getID();
        }
    }

    return maxID;
}

// Part two: a bit more complicated: we need to find my seat
int partTwo(const std::vector<BoardingPass>& passes) {
    std::map<int, std::pair<int, int>> seats;
    int id = -999;

    // use a map, and we'll sort on ID
    for (auto& p : passes) {
        seats[p.getID()] = p.getCoords();
    }

    // use an iterator to find the first instance where the prev or next id doesn't match
    for (std::map<int, std::pair<int, int>>::iterator it = std::next(seats.begin()); it != std::prev(seats.end()); it++) {
        auto prevValue = std::prev(it, 1)->first;
        auto currValue = it->first;
        auto nextValue = std::next(it, 1)->first;
        if (prevValue != currValue - 1) {
            id = it->first - 1;
            break;
        } else if ( nextValue != currValue + 1) {
            id = it->first + 1;
            break;
        }
    }
    
    return id;
}

int main() {
   std::ifstream in("../Inputs/Day_05.txt");
   std::string line;
   std::vector<BoardingPass> passes;
   while (std::getline(in, line)) {
      passes.emplace_back(std::move(line));
   }

   std::cout << "Part One: " << partOne(passes) << std::endl;
   std::cout << "Part Two: " << partTwo(passes) << std::endl;

   return 0;
}