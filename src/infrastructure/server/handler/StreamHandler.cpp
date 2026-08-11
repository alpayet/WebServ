#include "infrastructure/server/handler/StreamHandler.hpp"

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/reactor/Reactor.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "infrastructure/server/utils/utils.hpp"

#include <iostream>
#include <signal.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

namespace webserv {
namespace handler {

StreamHandler::StreamHandler(const app::StreamInfo stream_info,
                             const int client_fd,
                             appProtocol::IProtocol *protocol)
    : m_stream_info(stream_info), m_client_fd(client_fd),
      m_app_protocol(protocol), m_read_buf(), m_last_activity(ft::now()) {}

StreamHandler::~StreamHandler() {}

int StreamHandler::getFd() const { return m_stream_info.fd; }

std::time_t StreamHandler::getLastActivity() const { return m_last_activity; }

void StreamHandler::onReadable(reactor::Reactor &reactor) {
  m_last_activity = ft::now();

  const ssize_t bytes_read =
      ::read(m_stream_info.fd, m_read_buf, RECV_CHUNK);
  if (bytes_read < 0) {
    // TODO:
    // voir avec alpayet si je dois pas pushStream Error pour renvoyer une
    // certaine page
    // also voir si fd et pid peuvent etre -1
    // reactor.modifyEventFlag(m_client_fd, reactor::EVENT_WRITE);

    kill(m_stream_info.pid, SIGKILL);
    waitpid(m_stream_info.pid, NULL, WNOHANG);
    reactor.removeEventHandler(m_client_fd);
    reactor.removeEventHandler(m_stream_info.fd);
    ::close(m_stream_info.fd);
    return;
  }

  appProtocol::IProtocol::StreamStatus::Type push_status =
      appProtocol::IProtocol::StreamStatus::NORMAL;

  if (bytes_read == 0)
    push_status = appProtocol::IProtocol::StreamStatus::END_OF_STREAM;

  DEBUG("read " << bytes_read << " bytes");

  const appProtocol::IProtocol::PushStatus::Type push_state =
      m_app_protocol->pushStream(m_read_buf, bytes_read, push_status);

  if (push_state == appProtocol::IProtocol::PushStatus::COMPLETE) {
    kill(m_stream_info.pid, SIGKILL);
    waitpid(m_stream_info.pid, NULL, WNOHANG);
    reactor.modifyEventFlag(m_client_fd, reactor::EVENT_WRITE);
    reactor.removeEventHandler(m_stream_info.fd);
    ::close(m_stream_info.fd);
  }
  // TODO if error...
}

void StreamHandler::onWritable(reactor::Reactor &reactor) {
  DEBUG("on writable cgi | should not happen");
}

void StreamHandler::onTimeout(reactor::Reactor &reactor) {

  m_last_activity = ft::now();
  std::cout << "update fd:" << m_stream_info.fd
            << " cgi on timeout last activity time_t: " << m_last_activity
            << std::endl;

  m_app_protocol->pushStream(NULL, 0,
                             appProtocol::IProtocol::StreamStatus::TIMEOUT);

  kill(m_stream_info.pid, SIGKILL);
  waitpid(m_stream_info.pid, NULL, WNOHANG);
  reactor.modifyEventFlag(m_client_fd, reactor::EVENT_WRITE);
  reactor.removeEventHandler(m_stream_info.fd);
  ::close(m_stream_info.fd);
}

} // namespace handler
} // namespace webserv