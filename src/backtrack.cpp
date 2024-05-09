#include "backtrack.h"
#include "utils.h"

namespace backtrack {

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
            std::cout << "Previous solutions...\n";
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
} // namespace backtrack
