#include "server/handler/ConnectionHandler.hpp"

#include "server/protocol/IProtocol.hpp"
#include "server/reactor/EventType.hpp"
#include "server/reactor/Reactor.hpp"
#include "server/transport/ITransport.hpp"
#include "server/utils/Logger.hpp"

#include <string>

namespace {
const std::size_t RECV_CHUNK = 64u * 1024u;
}

namespace webserv {
namespace handler {

ConnectionHandler::ConnectionHandler(transport::ITransport *connection,
                                     protocol::IProtocol *protocol)
    : m_transport(connection), m_protocol(protocol), m_read_buf(RECV_CHUNK),
      m_write_buf(), m_write_pos(0) {}

ConnectionHandler::~ConnectionHandler() {
  delete m_transport;
  delete m_protocol;
}

int ConnectionHandler::getFd() const { return m_transport->getFd(); }

void ConnectionHandler::onReadable(reactor::Reactor &reactor) {
  m_read_buf.resize(RECV_CHUNK);

  const ssize_t bytes_read =
      m_transport->read(&m_read_buf[0], m_read_buf.size());

  if (bytes_read <= 0) {
    reactor.removeEventHandler(m_transport->getFd());
    return;
  }

  m_read_buf.resize(bytes_read);
  // DEBUG("read request, buffer : " << std::string(m_read_buf.begin(),
  // m_read_buf.end()));

  const protocol::IProtocol::ProtocolState state =
      m_protocol->request(m_read_buf);

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
  // DEBUG("send response, buffer : " << std::string(m_write_buf.begin(),
  //                                                 m_write_buf.end()));

  if (m_write_pos < m_write_buf.size()) {
    const ssize_t bytes_send = m_transport->write(
        &m_write_buf[m_write_pos], m_write_buf.size() - m_write_pos);
    if (bytes_send < 0) {
      reactor.removeEventHandler(m_transport->getFd());
      return;
    }
    m_write_pos += static_cast<std::size_t>(bytes_send);
  }

  if (m_write_pos < m_write_buf.size())
    return;

  m_write_buf.clear();
  m_write_pos = 0;

  if (!m_protocol->isResponseComplete()) {
    const std::vector<char> &chunk = m_protocol->response();
    m_write_buf.assign(chunk.begin(), chunk.end());
    return;
  }

  if (m_protocol->shouldKeepAlive()) {
    m_protocol->reset();
    reactor.modifyEventFlag(m_transport->getFd(), reactor::EVENT_READ);
  } else
    reactor.removeEventHandler(m_transport->getFd());
}

} // namespace handler
} // namespace webserv
