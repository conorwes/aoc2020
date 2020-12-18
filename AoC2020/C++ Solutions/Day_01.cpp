#include "common.h"

// Handy function which accepts a vector of ints of any size and sums members
int sumN(const std::vector<int>& values)
{
   int sum;
   for(auto i : values)
      sum += i;

   return sum;
}

// Part One: Find the pair which sums to 2020 and return their product.
int partOne(const std::vector<int>& vec) {
   int sum;
   for (size_t i = 0; i < vec.size(); i++) {
      for (size_t j = i + 1; j < vec.size(); j++) {
         sum = sumN({vec.at(i), vec.at(j)});
         if (sum == 2020)
            return vec.at(i) * vec.at(j);
      }
   }

   // If no such pair found, return 1.
   return 1;
}

// Part Two: Find the trio which sums to 2020 and return their product.
int partTwo(const std::vector<int>& vec) {
   int sum;
   for (size_t i = 0; i < vec.size(); i++) {
      for(size_t j = 0; j < vec.size(); j++) {
         for (size_t k = 0; k < vec.size(); k++) {
            sum = sumN({vec.at(i), vec.at(j), vec.at(k)});
            if (sum == 2020)
               return vec.at(i) * vec.at(j) * vec.at(k);
         }
      }
   }

   // If no such pair found, return 1.
   return 1;
}


int main() {
   std::ifstream in("../Inputs/Day_01.txt");
   std::string buf;
   std::vector<int> vec;
   while (std::getline(in, buf)) {
      vec.push_back(std::stoi(buf));
   }

   std::cout << "Part One: " << partOne(vec) << std::endl;
   std::cout << "Part Two: " << partTwo(vec) << std::endl;

   return 0;
}
