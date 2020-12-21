#include "common.h"

using namespace std;
using ll = long long;

vector<string> input;

ll evaluateP1(string exp) {
    // our strategy here is simple: reduce all subexpressions to values so we end up at 
    // one level and can just process in order
    size_t posClose;
    while ((posClose = exp.find(')')) != string::npos) {
        auto posOpen = exp.rfind('(', posClose);
        auto subExp = exp.substr(posOpen + 1, posClose - posOpen - 1);
        ll val = evaluateP1(subExp);
        exp.erase(posOpen, (posClose - posOpen + 1));
        exp.insert(posOpen, to_string(val));
    }

    stringstream ss{exp};
    string op;
    ll lhs, rhs;
    ss >> lhs;
    while (ss >> op >> rhs) {
        if (op == "+") {
            lhs += rhs;
        } else if (op == "*") {
            lhs *= rhs;
        } else {
            // houston, we've had a problem
        }
    }
    return lhs;
}

ll evaluateP2(string exp) {
    // the strategy here is the same but more nuanced - now we use the multiplicative operator 
    // in addition to parentheses as our marker for subexpressions
    size_t posClose;
    while ((posClose = exp.find(')')) != string::npos) {
        auto posOpen = exp.rfind('(', posClose);
        auto subExp = exp.substr(posOpen + 1, posClose - posOpen - 1);
        ll val = evaluateP2(subExp);
        exp.erase(posOpen, (posClose - posOpen + 1));
        exp.insert(posOpen, to_string(val));
    }
    
    size_t posMult;
    while ((posMult = exp.find('*')) != string::npos) {
        auto subLHS = exp.substr(0, posMult);
        auto subRHS = exp.substr(posMult + 1);
        return evaluateP2(subLHS) * evaluateP2(subRHS);
    }

    stringstream ss{exp};
    string op;
    ll lhs, rhs;
    ss >> lhs;
    while (ss >> op >> rhs) {
        if (op == "+") {
            lhs += rhs;
        } else if (op == "*") {
            lhs *= rhs;
        } else {
            // houston, we've had a problem
        }
    }
    return lhs;
} 

ll partOne() {
    ll sum{0};
    auto p1Input = input;
    for (auto& p : p1Input) {
        sum += evaluateP1(p);
    }

    return sum;
}

ll partTwo() {
    ll sum{0};
    auto p2Input = input;
    for (auto& p : p2Input) {
        sum += evaluateP2(p);
    }

    return sum;
}

int main() {
    ifstream in("../Inputs/Day_18.txt");
    string worker;
    while(getline(in, worker)) {
        input.emplace_back(worker);
    }

    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}