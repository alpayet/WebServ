#include "server/protocol/HttpProtocol.hpp"

#include "infrastructure/http/Handler.hpp"
#include "server/utils/Logger.hpp"

namespace webserv {
namespace protocol {

HttpProtocol::HttpProtocol(http::Handler &handler)
    : m_context(), m_handler(handler) {
  DEBUG("new httpProtocol/client, new context ");
}

HttpProtocol::~HttpProtocol() {
  DEBUG("httpProtocol destructor, reset HttpProtocol context ");
}

// TODO:
//  IProtocol::ProtocolState HttpProtocol::request(std::vector<char> &buffer,
//  requestStatus) {
IProtocol::ProtocolState HttpProtocol::request(std::vector<char> &buffer) {

  DEBUG("new request call");

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

const std::vector<char> &HttpProtocol::response() {
  return m_handler.pull(m_context);
}

bool HttpProtocol::isResponseComplete() {
  return m_handler.isResponseComplete(m_context);
}

void HttpProtocol::reset() {}

bool HttpProtocol::shouldKeepAlive() const { return false; }

} // namespace protocol
} // namespace webserv
