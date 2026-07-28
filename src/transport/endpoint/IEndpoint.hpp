#ifndef IENDPOINT_HPP
#define IENDPOINT_HPP

#include <stdexcept>
#include <string>

namespace webserv {

namespace reactor {
class Reactor;
}

namespace transport {

class IEndpoint {
public:
  virtual ~IEndpoint() {}

  virtual void open(reactor::Reactor &reactor) = 0;

  virtual std::string formatEndpoint() const = 0;

  class Exception : public std::runtime_error {
  public:
    explicit Exception(const std::string &what)
        : std::runtime_error("Endpoint error: " + what) {}
  };
};

} // namespace transport
} // namespace webserv

#endif
