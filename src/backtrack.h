#pragma once

#include "utils.h"
#include <cctype>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace backtrack {
std::vector<std::set<uint32_t>> find_solution_set(
    std::vector<uint32_t> &bitwords,
    std::unordered_map<uint32_t, std::vector<std::string>> bit2words);
}
