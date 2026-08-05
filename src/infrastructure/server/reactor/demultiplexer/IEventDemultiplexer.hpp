#ifndef IEVENTDEMULTIPLEXER_HPP
#define IEVENTDEMULTIPLEXER_HPP

namespace webserv {
namespace reactor {

class IEventDemultiplexer {
public:
  virtual ~IEventDemultiplexer() {}

  virtual bool add(int fd, int flag) = 0;
  virtual bool modify(int fd, int flag) = 0;
  virtual bool remove(int fd) = 0;

  virtual int wait(int timeout_ms) = 0;

  virtual int getEventFd(int index) const = 0;
  virtual bool isReadable(int index) const = 0;
  virtual bool isWritable(int index) const = 0;
  virtual bool isError(int index) const = 0;
};

} // namespace reactor
} // namespace webserv

#endif
