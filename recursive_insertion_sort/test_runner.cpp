// Supplied test driver. You do not need to read or modify this file.
//
// `make test` builds and runs it. It checks that your implementation is
// recursive, runs every case in tests/, and checks that a call with
// n < ar.size() leaves the rest of the vector alone.

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "import_numbers_from_file.h"
#include "recursive_insertion_sort.h"

namespace {

std::string join(const std::vector<int> &ar) {
  std::ostringstream out;
  for (std::size_t k = 0; k < ar.size(); ++k) {
    if (k > 0) {
      out << ", ";
    }
    out << ar[k];
  }
  return out.str();
}

std::string trim(const std::string &s) {
  const std::size_t b = s.find_first_not_of(" \t\r\n");
  if (b == std::string::npos) {
    return "";
  }
  return s.substr(b, s.find_last_not_of(" \t\r\n") - b + 1);
}

std::string readFile(const std::filesystem::path &p) {
  std::ifstream in(p);
  std::ostringstream buf;
  buf << in.rdbuf();
  return buf.str();
}

// Strip // and /* */ comments so a call mentioned in a comment does not count.
std::string stripComments(const std::string &src) {
  std::string out;
  for (std::size_t i = 0; i < src.size();) {
    if (src.compare(i, 2, "//") == 0) {
      while (i < src.size() && src[i] != '\n') {
        ++i;
      }
    } else if (src.compare(i, 2, "/*") == 0) {
      const std::size_t end = src.find("*/", i + 2);
      i = (end == std::string::npos) ? src.size() : end + 2;
    } else {
      out += src[i++];
    }
  }
  return out;
}

bool isRecursive(const std::string &path) {
  const std::string code = stripComments(readFile(path));
  const std::string name = "recursiveInsertionSort";
  int hits = 0;
  for (std::size_t i = code.find(name); i != std::string::npos;
       i = code.find(name, i + name.size())) {
    ++hits;
  }
  return hits >= 2;  // one for the definition, at least one for a call
}

void report(bool ok, const std::string &label, int &failures) {
  std::cout << (ok ? "PASS  " : "FAIL  ") << label << '\n';
  if (!ok) {
    ++failures;
  }
}

}  // namespace

int main() {
  int failures = 0;

  report(isRecursive("recursive_insertion_sort.cpp"),
         "recursion  (a call to recursiveInsertionSort in your code)",
         failures);

  const std::filesystem::path dir = "tests";
  if (!std::filesystem::is_directory(dir)) {
    std::cerr << "Cannot find the tests/ directory. Run make from the folder "
                 "that holds the makefile.\n";
    return 1;
  }

  std::vector<std::filesystem::path> inputs;
  for (const auto &entry : std::filesystem::directory_iterator(dir)) {
    const std::string name = entry.path().filename().string();
    if (name.rfind("input_", 0) == 0 && entry.path().extension() == ".txt") {
      inputs.push_back(entry.path());
    }
  }
  std::sort(inputs.begin(), inputs.end());

  for (const auto &in : inputs) {
    const std::string stem =
        in.filename().string().substr(6);  // after "input_"
    const std::string label = stem.substr(0, stem.size() - 4);  // before ".txt"
    const std::filesystem::path expected = dir / ("expected_" + label + ".txt");

    // A case you added yourself, with no expected output to compare against.
    if (!std::filesystem::is_regular_file(expected)) {
      std::cout << "SKIP  " << label << "  (no expected_" << label << ".txt)\n";
      continue;
    }

    std::vector<int> ar;
    try {
      ar = importNumbersFromFile(in.string());
    } catch (const std::exception &ex) {
      std::cout << "FAIL  " << label
                << "  (could not read the input: " << ex.what() << ")\n";
      ++failures;
      continue;
    }
    recursiveInsertionSort(ar, ar.size());
    report(join(ar) == trim(readFile(expected)), label, failures);
  }

  // The contract says elements from index n onwards are left alone.
  std::vector<int> partial = {5, 4, 3, 2, 1};
  recursiveInsertionSort(partial, 3);
  // The size check has to come first. Building the sorted prefix in a new
  // vector and assigning it back shortens partial, and the reads below would
  // then be past the end.
  const bool prefix_ok = partial.size() == 5 &&
                         std::is_sorted(partial.begin(), partial.begin() + 3) &&
                         partial[3] == 2 && partial[4] == 1;
  report(prefix_ok,
         "prefix  (sorting the first 3 of 5 keys leaves the rest alone)",
         failures);

  if (failures == 0) {
    std::cout << "\nAll checks passed.\n";
  } else {
    std::cout << "\n"
              << failures
              << " check(s) failed. Use 'make run FILE=input_<name>.txt'"
              << " to look at one case.\n";
  }
  return failures == 0 ? 0 : 1;
}
