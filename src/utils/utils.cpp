#include "utils.hpp"

#include <sstream>

namespace ft {
std::string intToString(int n) {
  std::stringstream ss;
  ss << n;
  return ss.str();
}
}  // namespace ft