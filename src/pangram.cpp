#include "pangram.h"
#include "utils.h"
#include <unordered_map>

using namespace std;

namespace pangram {

vector<set<uint32_t>>
find_solution_set(vector<uint32_t> &bitwords,
                  unordered_map<uint32_t, vector<string>> bit2words) {

  unordered_map<uint32_t, vector<set<uint32_t>>> partialSols;
  partialSols[(1 << 26) - 1] =
      vector<set<uint32_t>>{set<uint32_t>()}; // end case

  function<bool(uint32_t, int, set<uint32_t>)> findPartialSols =
      [&](uint32_t currSum, int idx, set<uint32_t> currSet) -> bool {
    if (partialSols.find(currSum) != partialSols.end()) {
      // if reached a partial sol, simply add all found paths to initial
      // solution
      for (auto parSol : partialSols[currSum]) {
        set<uint32_t> sol(currSet);
        sol.insert(parSol.begin(), parSol.end());
        partialSols[0].push_back(sol);
      }
      if (currSum == (1 << 26) - 1)
        printResult(partialSols[0], bit2words);
      return true; // found solution
    } else {
      vector<set<uint32_t>> partialSol; // all partial sols from here
      bool found = false;

      for (int i = idx; i < (int)bitwords.size(); i++) {
        if ((currSum & bitwords[i]) == 0) { // possible candidate
          currSet.insert(bitwords[i]);
          // add to set and try to find recursive solution
          if (findPartialSols(currSum + bitwords[i], i + 1, currSet)) {
            found = true;
            for (auto sol : partialSols[currSum + bitwords[i]]) {
              // for each solution found we add the partial solution
              // to this current sum
              set<uint32_t> singleSol(sol);
              singleSol.insert(bitwords[i]);
              partialSol.push_back(singleSol);
            }
          }
          currSet.erase(bitwords[i]);
        }
      }

      if (found) {
        partialSols[currSum] = partialSol;
      }
      return found;
    }
  };

  findPartialSols(0, 0, set<uint32_t>());

  return partialSols[0];
}

} // namespace pangram
