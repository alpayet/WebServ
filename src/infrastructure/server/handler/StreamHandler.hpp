#ifndef STREAMHANDLER_HPP
#define STREAMHANDLER_HPP

#include "application/ports/IDynamicResourceExecutor.hpp"
#include "infrastructure/server/handler/IEventHandler.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

#include <cstddef>
#include <sys/types.h>
#include <vector>

namespace webserv {

namespace appProtocol {
class IProtocol;
}

namespace handler {

class StreamHandler : public IEventHandler {
public:
  StreamHandler(app::StreamResources stream_resources, int client_fd,
                appProtocol::IProtocol *protocol);
  ~StreamHandler();

  int getFd() const;
  std::time_t getLastActivity() const;

  void onReadable(reactor::Reactor &reactor);
  void onWritable(reactor::Reactor &reactor);
  void onTimeout(reactor::Reactor &reactor);

private:
  StreamHandler(const StreamHandler &);
  StreamHandler &operator=(const StreamHandler &);

  static std::size_t const RECV_CHUNK = 16 * 1024;

  app::StreamResources m_stream_resources;
  int m_client_fd;
  appProtocol::IProtocol *m_app_protocol;
  char m_read_buf[RECV_CHUNK];
  std::time_t m_last_activity;
};

} // namespace handler
} // namespace webserv

#endif // CGISTREAMHANDLER_HPP
