#include "insertion_sort.h"

#include <cstddef>
#include <vector>

void insertionSort(std::vector<int> &a) {
  for (std::size_t i = 1; i < a.size(); ++i) {
    const int active_key = a[i];
    std::size_t h = i;
    while (h > 0 && a[h - 1] > active_key) {
      a[h] = a[h - 1];
      --h;
    }
    a[h] = active_key;
  }
}
