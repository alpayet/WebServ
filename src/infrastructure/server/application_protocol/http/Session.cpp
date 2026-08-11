#include "infrastructure/server/application_protocol/http/Session.hpp"
#include "infrastructure/server/application_protocol/http/core/Protocol.hpp"
#include "infrastructure/server/utils/Logger.hpp"

namespace http {

Session::Session(Protocol &handler) : _context(), _protocol(handler) {}

Session::PushStatus::Type Session::pushRequest(char const *inputBuf,
                                               std::size_t size,
                                               RequestStatus::Type status) {
  return (_protocol.pushRequest(_context, inputBuf, size, status));
}

Session::PushStatus::Type Session::pushStream(char const *streamBuf,
                                              std::size_t size,
                                              StreamStatus::Type status) {
  return (_protocol.pushStream(_context, streamBuf, size, status));
}

Session::PullStatus::Type Session::pullResponse(std::vector<char> &outputBuf) {
  return (_protocol.pullResponse(_context, outputBuf));
}

app::StreamInfo Session::getStreamResources(void) const {
  const app::StreamInfo resources = {_context.stream.stream_info.fd,
                                          _context.stream.stream_info.pid};

  return resources;
}

void Session::reset(void) { _context.reset(); }

bool Session::shouldKeepAlive(void) const { return (_context.shouldKeepAlive); }
} // namespace http
