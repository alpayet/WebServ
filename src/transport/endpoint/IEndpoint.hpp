#ifndef ILISTENER_HPP
#define ILISTENER_HPP

namespace webserv {

namespace reactor {
class Reactor;
}

namespace transport {

class IEndpoint {
public:
  virtual ~IEndpoint() {}

  virtual void openEndpoint(reactor::Reactor &reactor) = 0;
};

} // namespace transport
} // namespace webserv

#endif
