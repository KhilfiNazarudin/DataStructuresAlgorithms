#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "import_numbers_from_file.h"
#include "merge_sort.h"

int main(int argc, char *argv[]) {
  enum ExitCode {
    ok = EXIT_SUCCESS,
    fail = 1,
    usage = 2,
    io = 3,
    bad_input = 4,
  };

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return usage;
  }

  try {
    const std::string filename = argv[1];
    std::vector<int> ar = importNumbersFromFile(filename);
    if (!ar.empty()) {
      mergeSort(ar, 0, ar.size() - 1);
    }

    for (std::size_t k = 0; k < ar.size(); ++k) {
      if (k > 0) {
        std::cout << ", ";
      }
      std::cout << ar[k];
    }
    std::cout << '\n';
    return ok;
  } catch (const std::runtime_error &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return io;
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return bad_input;
  }
}
