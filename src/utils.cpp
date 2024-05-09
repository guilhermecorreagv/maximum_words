#include "utils.h"

unsigned int countSetBits(unsigned int n) {
  // count number of 1s in a uint
  unsigned int count = 0;
  while (n) {
    n &= (n - 1);
    count++;
  }
  return count;
}
