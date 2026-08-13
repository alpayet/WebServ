#include "infrastructure/server/handler/ConnectionHandler.hpp"

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/handler/StreamHandler.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/reactor/Reactor.hpp"
#include "infrastructure/server/transport_protocol/ITransport.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "infrastructure/server/utils/utils.hpp"

#include <sys/types.h>

namespace webserv {
    namespace handler {

        ConnectionHandler::ConnectionHandler(transport::ITransport* connection, appProtocol::IProtocol* appProtocol) :
            m_transport(connection), m_app_protocol(appProtocol), m_read_buf(), m_write_buf(), m_write_pos(0),
            m_streaming(false), m_last_activity(ft::now())
        {}

        ConnectionHandler::~ConnectionHandler()
        {
            delete m_transport;
            delete m_app_protocol;
        }

        int ConnectionHandler::getFd() const { return m_transport->getFd(); }

        std::time_t ConnectionHandler::getLastActivity() const
        {
            if (m_streaming)
                return -1;
            return m_last_activity;
        }

        void ConnectionHandler::onReadable(reactor::Reactor& reactor)
        {
            DEBUG("New request");

            const ssize_t bytes_read = m_transport->read(m_read_buf, RECV_CHUNK);

            m_last_activity = ft::now();

            if (bytes_read <= 0)
            {
                reactor.removeEventHandler(m_transport->getFd());
                return;
            }

            if (bytes_read < 1500)
                DEBUG("read request on fd: " << m_transport->getFd()
                                             << ", buffer : " << std::string(m_read_buf, bytes_read));
            else
                DEBUG("read request, buffer too long must be img ");

            const appProtocol::IProtocol::PushStatus::Type push_state =
                m_app_protocol->pushRequest(m_read_buf, bytes_read, appProtocol::IProtocol::RequestStatus::NORMAL);

            if (push_state == appProtocol::IProtocol::PushStatus::COMPLETE)
            {
                m_write_pos = 0;
                reactor.modifyEventFlag(m_transport->getFd(), reactor::EVENT_WRITE);
            }
            else if (push_state == appProtocol::IProtocol::PushStatus::STREAM_AVAILABLE)
            {
                try
                {
                    IEventHandler* event =
                        new StreamHandler(m_app_protocol->getStreamResources(), m_transport->getFd(), m_app_protocol);
                    if (!reactor.addEventHandler(event, reactor::EVENT_READ))
                        throw std::runtime_error("can't add cgi event handler");

                    m_streaming = true;
                    reactor.releaseFromDemux(m_transport->getFd());
                }
                catch (...)
                {
                    DEBUG("throw on new Cgi");
                    reactor.removeEventHandler(m_transport->getFd());
                }
            }
        }

        void ConnectionHandler::onWritable(reactor::Reactor& reactor)
        {
            // DEBUG("send response, " << m_transport->getFd()
            //                         << ", buffer : " << std::string(m_write_buf.begin(), m_write_buf.end()));

            m_streaming = false;
            m_last_activity = ft::now();

            if (m_write_pos < m_write_buf.size())
            {
                const ssize_t bytes_send =
                    m_transport->write(&m_write_buf[m_write_pos], m_write_buf.size() - m_write_pos);
                if (bytes_send < 0)
                {
                    reactor.removeEventHandler(m_transport->getFd());
                    return;
                }
                m_write_pos += static_cast<std::size_t>(bytes_send);
            }

            if (m_write_pos < m_write_buf.size())
                return;

            m_write_buf.clear();
            m_write_pos = 0;

            const appProtocol::IProtocol::PullStatus::Type pull_state = m_app_protocol->pullResponse(m_write_buf);


            if (!m_write_buf.empty())
                return;
            if (pull_state == appProtocol::IProtocol::PullStatus::HAS_MORE)
                return;

            if (m_app_protocol->shouldKeepAlive())
            {
                m_streaming = false;
                m_app_protocol->reset();
                reactor.modifyEventFlag(m_transport->getFd(), reactor::EVENT_READ);
            }
            else
                reactor.removeEventHandler(m_transport->getFd());
        }

        void ConnectionHandler::onTimeout(reactor::Reactor& reactor)
        {
            m_last_activity = ft::now();

            m_app_protocol->pushRequest(NULL, 0, appProtocol::IProtocol::RequestStatus::TIMEOUT);

            reactor.modifyEventFlag(m_transport->getFd(), reactor::EVENT_WRITE);
        }

    } // namespace handler
} // namespace webserv
