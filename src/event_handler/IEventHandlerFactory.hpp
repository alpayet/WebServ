#ifndef IEVENTHANDLERFACTORY_HPP
#define IEVENTHANDLERFACTORY_HPP

namespace webserv {

namespace reactor {
class IEventHandler;
}

namespace transport {

class IEventHandlerFactory {
public:
  virtual ~IEventHandlerFactory() {}

  virtual reactor::IEventHandler *instanceEventHandler(int fd) const = 0;
};

} // namespace transport
} // namespace webserv

#endif
