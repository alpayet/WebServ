#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

namespace webserv {

namespace reactor {
class Reactor;
}

namespace handler {

class IEventHandler {
public:
  virtual ~IEventHandler() {}

  virtual int getFd() const = 0;
  virtual void onReadable(reactor::Reactor &reactor) = 0;
  virtual void onWritable(reactor::Reactor &reactor) = 0;
};

} // namespace handler
} // namespace webserv

#endif
