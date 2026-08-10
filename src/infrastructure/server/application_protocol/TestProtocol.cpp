#include "infrastructure/server/application_protocol/TestProtocol.hpp"

#include "infrastructure/server/utils/utils.hpp"

namespace webserv {
namespace appProtocol {

TestProtocol::TestProtocol(const std::string &body)
    : m_request(), m_response() {
  const std::string raw = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/plain\r\n"
                          "Content-Length: " +
                          ft::intToString(static_cast<int>(body.size())) +
                          "\r\n"
                          "Connection: close\r\n"
                          "\r\n" +
                          body;
  m_response.assign(raw.begin(), raw.end());
}

TestProtocol::~TestProtocol() {}

TestProtocol::PushStatus::Type
TestProtocol::pushRequest(const char *inputBuf, const std::size_t size,
                          const RequestStatus::Type status) {
  (void)inputBuf;
  (void)size;
  (void)status;
  // if (len == 0)
  //   return SEND_OK;
  //
  // m_request.append(data, len);

  if (m_request.find("\r\n\r\n") == std::string::npos)
    return PushStatus::NEED_MORE_DATA;

  return PushStatus::COMPLETE;
}

TestProtocol::PushStatus::Type
TestProtocol::pushStream(const char *streamBuf, const std::size_t size,
                         const StreamStatus::Type status) {
  (void)streamBuf;
  (void)size;
  (void)status;
  return PushStatus::COMPLETE;
}

TestProtocol::PullStatus::Type
TestProtocol::pullResponse(std::vector<char> &outputBuf) {
  (void)outputBuf;
  return PullStatus::HAS_MORE;
}

app::StreamResources TestProtocol::getStreamResources() const {
  const app::StreamResources resources = {-1, -1};

  return resources;
}

void TestProtocol::reset() { m_request.clear(); }

bool TestProtocol::shouldKeepAlive() const { return false; }

TestProtocolFactory::TestProtocolFactory(const std::string &body)
    : m_body(body) {}

TestProtocolFactory::~TestProtocolFactory() {}

IProtocol *TestProtocolFactory::create() { return new TestProtocol(m_body); }

} // namespace appProtocol
} // namespace webserv
