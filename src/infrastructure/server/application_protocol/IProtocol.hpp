#ifndef IPROTOCOL_HPP
#define IPROTOCOL_HPP

#include <cstddef>
#include <vector>

namespace webserv {
namespace appProtocol {

class IProtocol {
public:
  enum ProtocolState {
    READ_MORE,
    READ_OK,
    SEND_MORE,
    SEND_OK,
    CLOSE_CONNECTION
  };

  enum PushStatus { NEED_MORE_DATA, PUSH_COMPLETE };

  enum PullStatus { HAS_MORE, PULL_COMPLETE };

  struct RequestStatus {
    enum Type { NORMAL, TIMEOUT };
  };

  struct StreamStatus {
    enum Type { NORMAL, TIMEOUT, END_OF_STREAM };
  };

  virtual ~IProtocol() {}

  virtual PushStatus pushRequest(std::vector<char> const &inputBuf,
                                 RequestStatus::Type status) = 0;
  virtual PushStatus pushStream(std::vector<char> const &streamBuf,
                                StreamStatus::Type status) = 0;

  virtual PullStatus pullResponse(std::vector<char> &outputBuf) = 0;

  virtual void reset(void) = 0;

  virtual bool shouldKeepAlive(void) const = 0;
};

} // namespace appProtocol
} // namespace webserv

#endif
