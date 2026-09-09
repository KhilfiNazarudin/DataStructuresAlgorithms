// This is the only file you should edit, and the only file you submit to
// Gradescope.
//
// The animator uses fresh left and right arrays inside each merge. This version
// instead reuses one scratch vector for the whole sort. The two sorted source
// ranges remain in ar; merge() writes their merged result to scratch and then
// copies that range back to ar.

#include "merge_sort.h"

#include <cstddef>
#include <vector>

void merge(std::vector<int> &ar, std::vector<int> &scratch, std::size_t lo,
           std::size_t md, std::size_t hi)
{
  std::size_t i = lo;
  std::size_t j = lo;
  std::size_t k = md+1;

  while ((j <= md) && (k <= hi))
  {
    if (ar[j] <= ar[k])
    {
      scratch[i] = ar[j];
      j++;
    }
    else
    {
      scratch[i] = ar[k];
      k++;
    }
    i++;
  }

  while (j <= md)
  {
    scratch[i] = ar[j];
    i++;
    j++;
  }

  while (k <= hi)
  {
    scratch[i] = ar[k];
    i++;
    k++;
  }

  for (std::size_t idx = lo; idx <= hi; idx++)
  {
    ar[idx] = scratch[idx];
  }
}

void mergeSortRange(std::vector<int> &ar, std::vector<int> &scratch,
                    std::size_t lo, std::size_t hi)
{
  if (lo < hi)
  {
    std::size_t md = (lo + hi) / 2;
    mergeSortRange(ar,scratch, lo, md);
    mergeSortRange(ar,scratch, md + 1, hi);
    merge(ar, scratch, lo, md, hi);
  }
}

// Already written for you. Allocate one auxiliary vector and reuse it through
// the entire recursive sort.
void mergeSort(std::vector<int> &ar, std::size_t lo, std::size_t hi)
{
  if (ar.empty() || lo >= hi)
  {
    return;
  }
  std::vector<int> scratch(ar.size());
  mergeSortRange(ar, scratch, lo, hi);
}