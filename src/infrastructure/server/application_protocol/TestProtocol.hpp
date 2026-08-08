#ifndef TESTPROTOCOL_HPP
#define TESTPROTOCOL_HPP

#include <string>
#include <vector>

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/application_protocol/IProtocolFactory.hpp"

namespace webserv {
namespace appProtocol {

class TestProtocol : public IProtocol {
public:
  explicit TestProtocol(std::string const &body);
  ~TestProtocol();

  PushStatus::Type pushRequest(char const *inputBuf, std::size_t size,
                         RequestStatus::Type status);
  PushStatus::Type pushStream(std::vector<char> const &streamBuf,
                        StreamStatus::Type status);

  PullStatus::Type pullResponse(std::vector<char> &outputBuf);

  void reset(void);

  bool shouldKeepAlive(void) const;

private:
  TestProtocol(TestProtocol const &);
  TestProtocol &operator=(TestProtocol const &);

  std::string m_request;
  std::vector<char> m_response;
};

class TestProtocolFactory : public IProtocolFactory {
public:
  explicit TestProtocolFactory(std::string const &body);
  ~TestProtocolFactory();

  IProtocol *create();

private:
  std::string m_body;
};

} // namespace appProtocol
} // namespace webserv

#endif
