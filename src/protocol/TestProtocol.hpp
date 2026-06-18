#ifndef TESTPROTOCOL_HPP
#define TESTPROTOCOL_HPP

#include <string>
#include <vector>

#include "protocol/IProtocol.hpp"
#include "protocol/IProtocolFactory.hpp"

namespace webserv {
namespace protocol {

class TestProtocol : public IProtocol {
public:
  explicit TestProtocol(const std::string &body);
  ~TestProtocol();

  ProtocolState receive(const char *data, std::size_t len);
  const std::vector<char> &response() const;
  void reset();
  bool shouldKeepAlive() const;

private:
  TestProtocol(const TestProtocol &);
  TestProtocol &operator=(const TestProtocol &);

  std::string m_read_buf;
  std::vector<char> m_write_buf;
  std::size_t m_write_buf_pos;
  bool m_complete;
};

class TestProtocolFactory : public IProtocolFactory {
public:
  explicit TestProtocolFactory(const std::string &body);
  ~TestProtocolFactory();

  IProtocol *create() const;

private:
  std::string m_body;
};

} // namespace protocol
} // namespace webserv

#endif
