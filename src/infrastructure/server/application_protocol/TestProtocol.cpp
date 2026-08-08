#include "infrastructure/server/application_protocol/TestProtocol.hpp"

#include "infrastructure/server/utils/utils.hpp"

namespace webserv {
namespace appProtocol {

TestProtocol::TestProtocol(std::string const &body)
    : m_request(), m_response() {
  std::string const raw = "HTTP/1.1 200 OK\r\n"
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

IProtocol::PushStatus
TestProtocol::pushRequest(char const *inputBuf, std::size_t size,
                          RequestStatus::Type status) {
  // if (len == 0)
  //   return SEND_OK;
  //
  // m_request.append(data, len);

  if (m_request.find("\r\n\r\n") == std::string::npos)
    return IProtocol::NEED_MORE_DATA;

  return IProtocol::PUSH_COMPLETE;
}

IProtocol::PushStatus
TestProtocol::pushStream(std::vector<char> const &streamBuf,
                         StreamStatus::Type status) {
  return IProtocol::PUSH_COMPLETE;
}

IProtocol::PullStatus TestProtocol::pullResponse(std::vector<char> &outputBuf) {
  return IProtocol::HAS_MORE;
}

void TestProtocol::reset() { m_request.clear(); }

bool TestProtocol::shouldKeepAlive() const { return false; }

TestProtocolFactory::TestProtocolFactory(std::string const &body)
    : m_body(body) {}

TestProtocolFactory::~TestProtocolFactory() {}

IProtocol *TestProtocolFactory::create() { return new TestProtocol(m_body); }

} // namespace appProtocol
} // namespace webserv
