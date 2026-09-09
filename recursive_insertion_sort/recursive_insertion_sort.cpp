#include "recursive_insertion_sort.h"

#include <cstddef>
#include <vector>

// Sort the first n keys of ar in ascending order using recursive insertion
// sort. Your implementation must call itself.
void recursiveInsertionSort(std::vector<int> &a, std::size_t n)
{
  // Base case.
  // INSERT YOUR CODE HERE
  if (n < 2)
    return;

  if (n > a.size())
    return;

  // Recursive step: sort the first n - 1 keys.
  // INSERT YOUR CODE HERE.
  recursiveInsertionSort(a, n - 1);

  std::size_t insert_pos = n - 1;
  const int active_key = a[n - 1];
  while (insert_pos > 0 && a[insert_pos - 1] > active_key)
  {
    a[insert_pos] = a[insert_pos - 1];
    --insert_pos;
  }
  a[insert_pos] = active_key;
  // Insertion step: insert the final key into the sorted prefix.
  // INSERT YOUR CODE HERE.
}
