#include "infrastructure/server/handler/StreamHandler.hpp"

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/reactor/Reactor.hpp"
#include "infrastructure/server/utils/utils.hpp"

#include <csignal>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

namespace webserv {
	namespace handler {

		StreamHandler::StreamHandler(const app::StreamInfo stream_info, const int client_fd,
		                             appProtocol::IProtocol* protocol) :
		    m_stream_info(stream_info), m_client_fd(client_fd), m_app_protocol(protocol), m_read_buf(),
		    m_last_activity(ft::now())
		{}

		StreamHandler::~StreamHandler() { releaseStreamResources(); }

		void StreamHandler::releaseStreamResources()
		{
			if (m_stream_info.pid != -1)
			{
				::kill(m_stream_info.pid, SIGKILL);
				::waitpid(m_stream_info.pid, NULL, 0);
				m_stream_info.pid = -1;
			}
			if (m_stream_info.fd != -1)
			{
				::close(m_stream_info.fd);
				m_stream_info.fd = -1;
			}
		}

		int StreamHandler::getFd() const { return m_stream_info.fd; }

		std::time_t StreamHandler::getLastActivity() const { return m_last_activity; }

		void StreamHandler::onReadable(reactor::Reactor& reactor)
		{
			m_last_activity = ft::now();

			appProtocol::IProtocol::StreamStatus::Type push_status = appProtocol::IProtocol::StreamStatus::NORMAL;

			const ssize_t bytes_read = ::read(m_stream_info.fd, m_read_buf, RECV_CHUNK);
			if (bytes_read < 0)
			{
				m_app_protocol->pushStream(m_read_buf, bytes_read, appProtocol::IProtocol::StreamStatus::ERROR);
				reactor.backToDemux(m_client_fd, reactor::EVENT_WRITE);
				reactor.removeEventHandler(m_stream_info.fd);

				releaseStreamResources();
				return;
			}

			if (bytes_read == 0)
				push_status = appProtocol::IProtocol::StreamStatus::END_OF_STREAM;

			const appProtocol::IProtocol::PushStatus::Type push_state =
			    m_app_protocol->pushStream(m_read_buf, bytes_read, push_status);

			if (push_state == appProtocol::IProtocol::PushStatus::COMPLETE)
			{
				reactor.backToDemux(m_client_fd, reactor::EVENT_WRITE);
				reactor.removeEventHandler(m_stream_info.fd);

				releaseStreamResources();
			}
		}

		void StreamHandler::onWritable(reactor::Reactor& reactor) { (void)reactor; }

		void StreamHandler::onTimeout(reactor::Reactor& reactor)
		{
			m_last_activity = ft::now();

			m_app_protocol->pushStream(NULL, 0, appProtocol::IProtocol::StreamStatus::TIMEOUT);
			reactor.backToDemux(m_client_fd, reactor::EVENT_WRITE);
			reactor.removeEventHandler(m_stream_info.fd);

			releaseStreamResources();
		}

	} // namespace handler
} // namespace webserv
