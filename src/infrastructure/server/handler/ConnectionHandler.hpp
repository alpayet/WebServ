#ifndef CONNECTIONHANDLER_HPP
#define CONNECTIONHANDLER_HPP

#include <cstddef>
#include <ctime>
#include <vector>

#include "infrastructure/server/handler/IEventHandler.hpp"

namespace webserv {

namespace reactor {
class Reactor;
}
namespace appProtocol {
class IProtocol;
}
namespace transport {
class ITransport;
}

namespace handler {

class ConnectionHandler : public IEventHandler {
public:
  ConnectionHandler(transport::ITransport *connection,
                    appProtocol::IProtocol *appProtocol);
  ~ConnectionHandler();

  int getFd() const;
  std::time_t getLastActivity() const;

  void onReadable(reactor::Reactor &reactor);
  void onWritable(reactor::Reactor &reactor);
  void onTimeout(reactor::Reactor &reactor);

private:
  ConnectionHandler(ConnectionHandler const &);
  ConnectionHandler &operator=(ConnectionHandler const &);

  transport::ITransport *m_transport;
  appProtocol::IProtocol *m_app_protocol;
  std::vector<char> m_read_buf;
  std::vector<char> m_write_buf;
  std::size_t m_write_pos;
  std::time_t m_last_activity;
};

} // namespace handler
} // namespace webserv

#endif
