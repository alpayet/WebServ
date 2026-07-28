#include "ConnectionHandler.hpp"

#include "protocol/IProtocol.hpp"
#include "reactor/EventType.hpp"
#include "reactor/Reactor.hpp"
#include "transport/ITransport.hpp"
#include "utils/Logger.hpp"

namespace webserv {
namespace handler {

namespace {
const std::size_t RECV_CHUNK = 64u * 1024u;
}

ConnectionHandler::ConnectionHandler(transport::ITransport *connection,
                                     protocol::IProtocol *protocol)
    : m_transport(connection), m_protocol(protocol), m_write_buf(),
      m_write_pos(0) {}

ConnectionHandler::~ConnectionHandler() {
  delete m_transport;
  delete m_protocol;
}

int ConnectionHandler::getFd() const { return m_transport->getFd(); }

void ConnectionHandler::onReadable(reactor::Reactor &reactor) {
  char buffer[RECV_CHUNK];
  const ssize_t bytes_read = m_transport->read(buffer, sizeof(buffer));

  if (bytes_read <= 0) {
    reactor.removeEventHandler(m_transport->getFd());
    return;
  }

  const protocol::IProtocol::ProtocolState state =
      m_protocol->receive(buffer, static_cast<std::size_t>(bytes_read));

  if (state == protocol::IProtocol::READ_OK) {
    const std::vector<char> &response = m_protocol->response();
    m_write_buf.assign(response.begin(), response.end());
    m_write_pos = 0;
    reactor.modifyEventFlag(m_transport->getFd(),
                            reactor::EVENT_READ | reactor::EVENT_WRITE);
  } else if (state == protocol::IProtocol::CLOSE_CONNECTION) {
    reactor.removeEventHandler(m_transport->getFd());
  }
}

void ConnectionHandler::onWritable(reactor::Reactor &reactor) {
  if (m_write_pos >= m_write_buf.size()) {
    reactor.modifyEventFlag(m_transport->getFd(), reactor::EVENT_READ);
    return;
  }

  const ssize_t bytes_send = m_transport->write(
      &m_write_buf[m_write_pos], m_write_buf.size() - m_write_pos);
  if (bytes_send < 0) {
    reactor.removeEventHandler(m_transport->getFd());
    return;
  }

  m_write_pos += static_cast<std::size_t>(bytes_send);

  if (m_write_pos < m_write_buf.size())
    return;

  m_write_buf.clear();
  m_write_pos = 0;

  const protocol::IProtocol::ProtocolState state = m_protocol->receive(0, 0);

  if (state == protocol::IProtocol::READ_OK) {
    const std::vector<char> &response = m_protocol->response();
    m_write_buf.assign(response.begin(), response.end());
  } else if (state == protocol::IProtocol::SEND_OK) {

    if (m_protocol->shouldKeepAlive()) {
      m_protocol->reset();
      reactor.modifyEventFlag(m_transport->getFd(), reactor::EVENT_READ);
    } else {
      reactor.removeEventHandler(m_transport->getFd());
    }
  }
}

} // namespace handler
} // namespace webserv
