#include "infrastructure/server/application_protocol/http/Session.hpp"
#include "infrastructure/server/application_protocol/http/core/Protocol.hpp"
#include "infrastructure/server/utils/Logger.hpp"

using webserv::appProtocol::IProtocol;

namespace http {

Session::Session(Protocol &handler) : _context(), _protocol(handler) {}

IProtocol::PushStatus
Session::pushRequest(std::vector<char> const &inputBuf, RequestStatus::Type status)
{
	return (_protocol.pushRequest(_context, inputBuf, status));
}

IProtocol::PushStatus
Session::pushStream(std::vector<char> const &streamBuf, StreamStatus::Type status)
{
	return (_protocol.pushStream(_context, streamBuf, status));
}

IProtocol::PullStatus Session::pullResponse(std::vector<char> &outputBuf)
{
	return (_protocol.pullResponse(_context, outputBuf));
}

void Session::reset(void) { _context.reset(); }

bool Session::shouldKeepAlive(void) const { return (_context.shouldKeepAlive); }
} // namespace http
