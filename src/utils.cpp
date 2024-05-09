#include "utils.h"

void printResult(
    std::vector<std::set<uint32_t>> res,
    std::unordered_map<uint32_t, std::vector<std::string>> bit2words) {

  // Function that prints the result
  // Receives the vector of sets of bitwords
  // and the reverse mapping from bitwords to words
  for (auto &r : res) {
    // For each possible result
    std::cout << "{\n \tResult: {\n";
    for (auto &bitword : r) {
      // For each bitword
      std::vector<std::string> words = bit2words[bitword];
      std::cout << "\t\t { ";
      // For each word associated with that bitword
      for (auto w : words)
        std::cout << w << ", ";
      std::cout << " }\n";
    }
    std::cout << "}\n";
  }
}

unsigned int countSetBits(unsigned int n) {
  // count number of 1s in a uint
  unsigned int count = 0;
  while (n) {
    n &= (n - 1);
    count++;
  }
  return count;
}
