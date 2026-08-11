#ifndef HTTPSESSION_HPP
#define HTTPSESSION_HPP

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"

namespace http {
class Protocol;

class Session : public webserv::appProtocol::IProtocol {
public:
  Session(Protocol &handler);
  virtual ~Session() {}

  virtual PushStatus::Type pushRequest(char const *inputBuf, std::size_t size,
                                       RequestStatus::Type status);
  virtual PushStatus::Type pushStream(char const *streamBuf, std::size_t size,
                                      StreamStatus::Type status);

  virtual PullStatus::Type pullResponse(std::vector<char> &outputBuf);

  virtual app::StreamInfo getStreamResources(void) const;

  virtual void reset(void);

  virtual bool shouldKeepAlive(void) const;

private:
  Session(Session const &);
  Session &operator=(Session const &);

  http::Context _context;
  http::Protocol &_protocol;
};

} // namespace http

#endif // HTTPSESSION_HPP
