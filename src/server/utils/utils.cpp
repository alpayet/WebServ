#include "server/utils/utils.hpp"

#include <sstream>

namespace ft {
std::string intToString(const int n) {
  std::stringstream ss;
  ss << n;
  return ss.str();
}
} // namespace ft