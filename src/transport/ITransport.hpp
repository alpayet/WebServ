#ifndef ITRANSPORT_HPP
#define ITRANSPORT_HPP

#include <sys/types.h>

#include <cstddef>

namespace webserv {
namespace transport {

class ITransport {
public:
  virtual ~ITransport() {}

  virtual int getFd() const = 0;

  virtual ssize_t read(char *buf, std::size_t len) = 0;
  virtual ssize_t write(const char *buf, std::size_t len) = 0;
};

} // namespace transport
} // namespace webserv

#endif
