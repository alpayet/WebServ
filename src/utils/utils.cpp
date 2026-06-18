#include "utils.hpp"

#include <fcntl.h>
#include <sstream>

namespace ft {
std::string intToString(const int n) {
  std::stringstream ss;
  ss << n;
  return ss.str();
}

bool setNonBlocking(const int fd) {
  return fcntl(fd, F_SETFL, O_NONBLOCK) != -1;
}
} // namespace ft