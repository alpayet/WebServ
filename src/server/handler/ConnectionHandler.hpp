#ifndef CONNECTIONHANDLER_HPP
#define CONNECTIONHANDLER_HPP

#include <cstddef>
#include <vector>

#include "server/handler/IEventHandler.hpp"

namespace webserv {

namespace reactor {
class Reactor;
}
namespace protocol {
class IProtocol;
}
namespace transport {
class ITransport;
}

namespace handler {

class ConnectionHandler : public IEventHandler {
public:
  ConnectionHandler(transport::ITransport *connection,
                    protocol::IProtocol *protocol);
  ~ConnectionHandler();

  int getFd() const;
  void onReadable(reactor::Reactor &reactor);
  void onWritable(reactor::Reactor &reactor);

private:
  ConnectionHandler(const ConnectionHandler &);
  ConnectionHandler &operator=(const ConnectionHandler &);

  transport::ITransport *m_transport;
  protocol::IProtocol *m_protocol;
  std::vector<char> m_read_buf;
  std::vector<char> m_write_buf;
  std::size_t m_write_pos;
};

} // namespace handler
} // namespace webserv

#endif
