#ifndef IPROTOCOL_HPP
#define IPROTOCOL_HPP

#include <cstddef>
#include <vector>

namespace webserv {
namespace protocol {

class IProtocol {
public:
  enum ProtocolState {
    READ_MORE,
    READ_OK,
    SEND_MORE,
    SEND_OK,
    CLOSE_CONNECTION
  };

  virtual ~IProtocol() {}

  virtual ProtocolState receive(std::vector<char> &buffer) = 0;
  virtual const std::vector<char> &response() = 0;
  virtual bool isResponseComplete() = 0;
  virtual void reset() = 0;
  virtual bool shouldKeepAlive() const = 0;
};

} // namespace protocol
} // namespace webserv

#endif
