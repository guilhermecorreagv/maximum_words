#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

void printResult(
    std::vector<std::set<uint32_t>> res,
    std::unordered_map<uint32_t, std::vector<std::string>> bit2words);
unsigned int countSetBits(unsigned int n);
