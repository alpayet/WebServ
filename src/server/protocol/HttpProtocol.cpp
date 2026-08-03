#include "server/protocol/HttpProtocol.hpp"

#include "infrastructure/http/Handler.hpp"
#include "server/utils/Logger.hpp"

namespace webserv {
namespace protocol {

HttpProtocol::HttpProtocol(http::Handler &handler)
    : m_context(), m_handler(handler) {}

HttpProtocol::~HttpProtocol() {}

// TODO:
//  IProtocol::ProtocolState HttpProtocol::request(std::vector<char> &buffer,
//  requestStatus) {
IProtocol::ProtocolState HttpProtocol::request(std::vector<char> &buffer) {

  const ITransfertHandler::ProcessingStatus status = m_handler.pushRequest(
      m_context, buffer, ITransfertHandler::RequestStatus::normal);

  switch (status) {
  case ITransfertHandler::needMoreData:
    return IProtocol::READ_MORE;
  case ITransfertHandler::complete:
    return IProtocol::READ_OK;
  default:
    return IProtocol::CLOSE_CONNECTION;
  }
}

bool HttpProtocol::response(std::vector<char> & r) {

  switch (m_handler.pull(m_context, r))
  {
    case ITransfertHandler::needMoreData:
      return false;
    case ITransfertHandler::complete:
      return true;
    default:
      return false;
  }
}

void HttpProtocol::reset() {m_context.reset();}

bool HttpProtocol::shouldKeepAlive() const { return true; }

} // namespace protocol
} // namespace webserv
