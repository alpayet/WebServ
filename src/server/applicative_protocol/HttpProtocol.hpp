#ifndef HTTPPROTOCOL_HPP
#define HTTPPROTOCOL_HPP

#include "infrastructure/http/Context.hpp"
#include "server/applicative_protocol/IProtocol.hpp"

namespace http {
class Handler;
}

namespace webserv {
namespace protocol {

class HttpProtocol : public IProtocol {
public:
  explicit HttpProtocol(http::Handler &handler);
  ~HttpProtocol();

  ProtocolState request(std::vector<char> &buffer);
  const std::vector<char> &response();
  bool isResponseComplete();
  void reset();
  bool shouldKeepAlive() const;

private:
  HttpProtocol(const HttpProtocol &);
  HttpProtocol &operator=(const HttpProtocol &);

  http::Context m_context;
  http::Handler &m_handler;
};

} // namespace protocol
} // namespace webserv

#endif // HTTPPROTOCOLFACTORY_HPP
