#ifndef IEVENTMANAGER_HPP
#define IEVENTMANAGER_HPP

class IEventManager {
 public:
  virtual ~IEventManager() {}

  enum { TYPE_READ, TYPE_WRITE };

  virtual bool addSocket(int fd, int filter, void* udata) = 0;
  virtual bool removeSocket(int fd) = 0;

  virtual int waitForEvents(int timeout_ms) = 0;

  virtual void* getUserData(int index) = 0;
  virtual int getEventFd(int index) = 0;
  virtual bool isReadEvent(int index) = 0;
};

#endif  // IEVENTMANAGER_HPP
