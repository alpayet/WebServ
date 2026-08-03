#include "server/utils/utils.hpp"

#include <iomanip>
#include <sstream>
#include <sys/time.h>

namespace ft {
std::string intToString(const int n) {
  std::stringstream ss;
  ss << n;
  return ss.str();
}

std::time_t now() { return std::time(0); }

std::string nowFormat() {
  struct timeval tv;
  gettimeofday(&tv, NULL);

  const std::time_t now = tv.tv_sec;
  const std::tm *lt = std::localtime(&now);

  char time_buffer[80];
  std::strftime(time_buffer, sizeof(time_buffer), "%Y/%m/%d %H:%M:%S", lt);

  const int milliseconds = tv.tv_usec / 1000;

  std::stringstream ss;
  ss << time_buffer << '.' << std::setfill('0') << std::setw(3) << milliseconds;

  return ss.str();
}

} // namespace ft