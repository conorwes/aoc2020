#include "common.h"
#include <algorithm>

using namespace std;
using ll = long long;

vector<string> input;
ll numCycles{6};
ll width, height, depth, wDim;

ll countNeighbors(const vector<vector<vector<bool>>>& grid, const ll& x, const ll& y, const ll& z) {
    ll count{0};

    for (ll iz = max(0ll, z - 1); iz < min(z + 2, depth); iz++) {
        for (ll iy = max(0ll, y - 1); iy < min(y + 2, height); iy++) {
            for (ll ix = max(0ll, x - 1); ix < min(x + 2, width); ix++) {
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

ll countNeighbors(const vector<vector<vector<vector<bool>>>>& grid, const ll& x, const ll& y, const ll& z, const ll& w) {
    ll count{0};
    for (ll iw = max(0ll, w - 1); iw < min(w + 2, wDim); iw++) {
        for (ll iz = max(0ll, z - 1); iz < min(z + 2, depth); iz++) {
            for (ll iy = max(0ll, y - 1); iy < min(y + 2, height); iy++) {
                for (ll ix = max(0ll, x - 1); ix < min(x + 2, width); ix++) {
                    if (grid[iw][iz][iy][ix]) {
                        count++;
                    }
                }
            }
        }
    }

    if (grid[w][z][y][x]) {
        count--;
    }
    return count;    
}

ll partOne() {
    width = (2 * numCycles) + input[0].size();
    height = (2 * numCycles) + input.size();
    depth = (2 * numCycles) + 1;

    vector<vector<vector<bool>>> grid (
        depth, vector<vector<bool>> (
            height, vector<bool> (
                width, false )));

    for (ll y = 0; y < input.size(); y++) {
        for (ll x = 0; x < input[y].size(); x++) {
            grid[numCycles][numCycles + y][numCycles + x] = input[y][x] == '#';
        }
    }

    ll lastCount;
    for (ll c = 0; c < numCycles; c++) {
        lastCount = 0;
        auto newGrid = grid;
        for (ll z = 0; z < depth; z++) {
            for (ll y = 0; y < height; y++) {
                for (ll x = 0; x < width; x++) {
                    ll neighbors = countNeighbors(grid, x, y, z);
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

        grid = move(newGrid);
    }

    return lastCount;
}

ll partTwo() {
    width = (2 * numCycles) + input[0].size();
    height = (2 * numCycles) + input.size();
    depth = (2 * numCycles) + 1;
    wDim = (2 * numCycles) + 1;

    vector<vector<vector<vector<bool>>>> grid (
        wDim, vector<vector<vector<bool>>> (
            depth, vector<vector<bool>> (
                height, vector<bool> (
                    width, false ))));

    for (ll y = 0; y < input.size(); y++) {
        for (ll x = 0; x < input[y].size(); x++) {
            grid[numCycles][numCycles][numCycles + y][numCycles + x] = input[y][x] == '#';
        }
    }

    ll lastCount;
    for (ll c = 0; c < numCycles; c++) {
        lastCount = 0;
        auto newGrid = grid;
        for (ll w = 0; w < wDim; w++) {
            for (ll z = 0; z < depth; z++) {
                for (ll y = 0; y < height; y++) {
                    for (ll x = 0; x < width; x++) {
                        ll neighbors = countNeighbors(grid, x, y, z, w);
                        if (grid[w][z][y][x]) {
                            newGrid[w][z][y][x] = (neighbors == 2) || (neighbors == 3);
                        } else {
                            newGrid[w][z][y][x] = (neighbors == 3);
                        }
                        if (newGrid[w][z][y][x]) {
                            lastCount++;
                        }
                    }
                }
            }
        }
        grid = move(newGrid);
    }

    return lastCount;
}

int main() {
    ifstream in("../Inputs/Day_17.txt");
    string worker;
    while(getline(in, worker)) {
        input.emplace_back(worker);
    }

    cout << "Part One: " << partOne() << endl;
    cout << "Part Two: " << partTwo() << endl;

    return 0;
}
