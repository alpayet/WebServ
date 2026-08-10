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

  struct PushStatus {
    enum Type { NEED_MORE_DATA, STREAM_AVAILABLE, COMPLETE };
  };

  struct PullStatus {
    enum Type { HAS_MORE, ERROR, COMPLETE };
  };

  struct RequestStatus {
    enum Type { NORMAL, TIMEOUT };
  };

  struct StreamStatus {
    enum Type { NORMAL, TIMEOUT, END_OF_STREAM };
  };

  virtual ~IProtocol() {}

  virtual PushStatus::Type pushRequest(char const *inputBuf, std::size_t size,
                                 RequestStatus::Type status) = 0;
  virtual PushStatus::Type pushStream(std::vector<char> const &streamBuf,
                                StreamStatus::Type status) = 0;

  virtual PullStatus::Type pullResponse(std::vector<char> &outputBuf) = 0;

  virtual int getStreamId(void) const = 0;

  virtual void reset(void) = 0;

  virtual bool shouldKeepAlive(void) const = 0;
};

} // namespace appProtocol
} // namespace webserv

#endif
