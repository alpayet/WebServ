#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

#include <ctime>

namespace webserv {

namespace reactor {
class Reactor;
}

namespace handler {

class IEventHandler {
public:
  virtual ~IEventHandler() {}

  virtual int getFd() const = 0;
  virtual std::time_t getLastActivity() const = 0;

  virtual void onReadable(reactor::Reactor &reactor) = 0;
  virtual void onWritable(reactor::Reactor &reactor) = 0;
  virtual void onTimeout(reactor::Reactor &reactor) = 0;
};

} // namespace handler
} // namespace webserv

#endif
