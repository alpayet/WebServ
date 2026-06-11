#ifndef ITRANSPORT_HPP
#define ITRANSPORT_HPP

#include <string>
#include <vector>

class ITransport {
 public:
  virtual ~ITransport() {}

  virtual void init() = 0;

  virtual std::vector<int> getReadableFds() = 0;

  virtual std::string processEvent(int fd) = 0;
  virtual void sendResponse(int fd, const std::string& data) = 0;

  virtual void closeConnection(int fd) = 0;
};

#endif  // ITRANSPORT_HPP
