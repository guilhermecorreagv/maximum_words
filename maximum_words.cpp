#include <cctype>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

const int MINIMUM_LETTERS = 3;

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

bool validLine(std::string &line) {
  // Valid words satisfy:
  // - have three or more letters
  // - do not have repeated characters
  // - only contain alphabetic characters (no ç or -)
  std::set<char> seen;
  for (auto c : line) {
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

std::vector<std::set<uint32_t>> find_solution_set(
    std::vector<uint32_t> &bitwords,
    std::unordered_map<uint32_t, std::vector<std::string>> bit2words) {
  std::vector<std::set<uint32_t>> res;
  int bestScore = 0;

  // this cancerous lambda function will do all the backtracking.
  // at each index we either choose to add (if valid) or skip the word.
  // if we find a new best length we print all the previous solutions found
  // so far.
  std::function<void(int, uint32_t, int, std::set<uint32_t>)> backtrack =
      [&](int idx, uint32_t currSum, int currScore,
          std::set<uint32_t> currSet) {
        if (idx == bitwords.size()) {
          // termination
          if (currScore > bestScore) {
            bestScore = currScore;
            std::cout << "Found new best score of " << bestScore << std::endl;
            printResult(res, bit2words);

            res.clear();
          }
          if (currScore == bestScore)
            res.push_back(currSet);
          return;
        }

        // case where we skip curr elem
        backtrack(idx + 1, currSum, currScore, currSet);
        if ((bitwords[idx] & currSum) == 0) {
          // case we add current word
          currSet.insert(bitwords[idx]);
          unsigned int score = countSetBits(bitwords[idx]);
          backtrack(idx + 1, currSum + bitwords[idx], currScore + score,
                    currSet);
          currSet.erase(bitwords[idx]); // not sure if this is needed
        }
      };

  backtrack(0, 0, 0, std::set<uint32_t>());
  return res;
}

int main() {

  std::ifstream inputFile("wordsList");

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

  std::vector<std::set<uint32_t>> res =
      find_solution_set(bitwordsvec, bit2words);
  std::cout << "Number of solutions found " << res.size() << std::endl;

  printResult(res, bit2words);
  return 0;
}
