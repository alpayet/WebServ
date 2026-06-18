#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

namespace webserv {
namespace reactor {

class Reactor;

class IEventHandler {
public:
  virtual ~IEventHandler() {}

  virtual int getHandlerFd() const = 0;
  virtual void onReadable(Reactor &reactor) = 0;
  virtual void onWritable(Reactor &reactor) = 0;
};

} // namespace reactor
} // namespace webserv

#endif
