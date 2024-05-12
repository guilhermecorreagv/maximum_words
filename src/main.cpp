#include "backtrack.h"
#include "pangram.h"
#include "utils.h"
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

const int MINIMUM_LETTERS = 3;

bool validLine(std::string &line) {
  // Valid words satisfy:
  // - have three or more letters
  // - do not have repeated characters
  // - only contain alphabetic characters (no ç or -)
  std::set<char> seen;
  for (auto ch : line) {
    char c = tolower(ch);
    if (line.length() < MINIMUM_LETTERS)
      return false;
    if (seen.find(c) != seen.end() || !isalpha(c))
      return false;
    seen.insert(c);
  }
  return true;
}

uint32_t word2bit(std::string &word) {
  // converts a string to binary
  uint32_t ret = 0;
  for (auto c : word)
    ret += 1 << (static_cast<int>(tolower(c)) - static_cast<int>('a'));
  return ret;
}

int main() {

  std::ifstream inputFile("./data/wordsList");

  if (!inputFile.is_open()) {
    std::cerr << "could not open file\n";
    return 1;
  }

  std::cout << "file opened successfully\n";

  std::string line;
  std::set<uint32_t> bitwords;
  std::vector<uint32_t> bitwordsvec;
  std::unordered_map<uint32_t, std::vector<std::string>> bit2words;

  int count = 0;
  while (getline(inputFile, line)) {
    if (validLine(line)) {
      uint32_t bitword = word2bit(line);  // get the bitword
      bit2words[bitword].push_back(line); // stores the reverse mapping
      count++;
      if (bitwords.find(bitword) != bitwords.end())
        continue;
      bitwords.insert(bitword);       // if it's a new bitword we record it
      bitwordsvec.push_back(bitword); // and push to the vector
    }
  }

  std::cout << "number of bitwords " << bitwords.size() << std::endl;
  std::cout << "number of words " << count << std::endl;

  std::vector<std::set<uint32_t>> res;

  // solution for perfect pangram
  res = pangram::find_solution_set(bitwordsvec, bit2words);

  //  brute force backtrack solution
  // res = backtrack::find_solution_set(bitwordsvec, bit2words);

  std::cout << "Number of solutions found " << res.size() << std::endl;

  printResult(res, bit2words);
  return 0;
}
