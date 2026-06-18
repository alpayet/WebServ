#include "protocol/TestProtocol.hpp"

#include "utils/utils.hpp"

namespace webserv {
namespace protocol {

TestProtocol::TestProtocol(const std::string &body)
    : m_read_buf(), m_write_buf(), m_complete(false) {
  std::string raw = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: " +
                    ft::intToString(static_cast<int>(body.size())) +
                    "\r\n"
                    "Connection: close\r\n"
                    "\r\n";
  raw += body;
  m_write_buf.assign(raw.begin(), raw.end());
}

TestProtocol::~TestProtocol() {}

IProtocol::ProtocolState TestProtocol::receive(const char *data,
                                               const std::size_t len) {
  if (m_complete)
    return READ_OK;

  m_read_buf.append(data, len);
  if (m_read_buf.find("\r\n\r\n") != std::string::npos) {
    m_complete = true;
    return READ_OK;
  }
  return READ_MORE;
}

#include <algorithm>

const std::vector<char> &TestProtocol::response() const {
  static bool first_call = true;
  static std::vector<char> chunk; // Vit pendant toute la durée du programme

  if (first_call) {
    first_call = false;
    std::size_t chunk_size =
        std::min(m_write_buf.size(), static_cast<std::size_t>(10));

    chunk.assign(m_write_buf.begin(), m_write_buf.begin() + chunk_size);
  } else {
    if (m_write_buf.size() > 10) {
      chunk.assign(m_write_buf.begin() + 10, m_write_buf.end());
    } else {
      chunk.clear();
    }
  }

  return chunk; // Safe car la variable static ne meurt pas à la fin de la
                // fonction
}

void TestProtocol::reset() {
  m_read_buf.clear();
  m_complete = false;
}

bool TestProtocol::shouldKeepAlive() const { return false; }

TestProtocolFactory::TestProtocolFactory(const std::string &body)
    : m_body(body) {}

TestProtocolFactory::~TestProtocolFactory() {}

IProtocol *TestProtocolFactory::create() const {
  return new TestProtocol(m_body);
}

} // namespace protocol
} // namespace webserv
