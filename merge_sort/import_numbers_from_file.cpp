#include "import_numbers_from_file.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

static std::string trim(const std::string &s) {
  std::size_t first = 0;
  while (first < s.size() &&
         std::isspace(static_cast<unsigned char>(s[first]))) {
    ++first;
  }
  std::size_t last = s.size();
  while (last > first &&
         std::isspace(static_cast<unsigned char>(s[last - 1]))) {
    --last;
  }
  return s.substr(first, last - first);
}

std::vector<int> importNumbersFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("could not open file: " + filename);
  }

  std::vector<int> numbers;
  std::string chunk;
  std::size_t token_no = 0;

  while (std::getline(file, chunk, ',')) {
    ++token_no;

    // Windows line endings
    if (!chunk.empty() && chunk.back() == '\r') {
      chunk.pop_back();
    }

    const std::string token = trim(chunk);
    if (token.empty()) {
      if (file.eof()) {
        continue;
      }
      throw std::invalid_argument("empty value near comma (token " +
                                  std::to_string(token_no) + ")");
    }

    std::istringstream iss(token);
    int x;
    if (!(iss >> x)) {
      throw std::invalid_argument("invalid integer in token " +
                                  std::to_string(token_no) + ": " + token);
    }

    char extra;
    if (iss >> extra) {
      throw std::invalid_argument("trailing characters in token " +
                                  std::to_string(token_no) + ": " + token);
    }

    numbers.push_back(x);
  }

  return numbers;
}
