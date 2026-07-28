#include "protocol/TestProtocol.hpp"

#include "utils/utils.hpp"

namespace webserv {
namespace protocol {

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

IProtocol::ProtocolState TestProtocol::receive(const char *data,
                                               const std::size_t len) {
  if (len == 0)
    return SEND_OK;

  m_request.append(data, len);

  if (m_request.find("\r\n\r\n") == std::string::npos)
    return READ_MORE;

  return READ_OK;
}

const std::vector<char> &TestProtocol::response() const { return m_response; }

void TestProtocol::reset() { m_request.clear(); }

bool TestProtocol::shouldKeepAlive() const { return false; }

TestProtocolFactory::TestProtocolFactory(const std::string &body)
    : m_body(body) {}

TestProtocolFactory::~TestProtocolFactory() {}

IProtocol *TestProtocolFactory::create() const {
  return new TestProtocol(m_body);
}

} // namespace protocol
} // namespace webserv
