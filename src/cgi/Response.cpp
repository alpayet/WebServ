/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 03:38:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/09 03:31:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Response.hpp"

namespace cgi {
unsigned short const Response::Status::DEFAULT_STATUS_CODE = 200;
char const			 Response::Status::DEFAULT_REASON[] = "OK";
unsigned short const Response::Status::DEFAULT_REDIR_STATUS_CODE = 302;
char const			 Response::Status::DEFAULT_REDIR_REASON[] = "Found";
char const			 Response::BODY_NAME_TEMPLATE[] = "cgi_response_body";

Response::Status::Status(void)
	: _statusCode(DEFAULT_STATUS_CODE), _reason(DEFAULT_REASON), _exists(false)
{}

unsigned short	   Response::Status::getStatusCode(void) const { return (_statusCode); }
std::string const &Response::Status::getReason(void) const { return (_reason); }

void Response::Status::setStatus(unsigned statusCode, std::string const &reason)
{
	_exists = true;
	_statusCode = statusCode;
	_reason = reason;
}

void Response::Status::setDefaultRedirStatus(void)
{
	_exists = true;
	_statusCode = Response::Status::DEFAULT_REDIR_STATUS_CODE;
	_reason = Response::Status::DEFAULT_REDIR_REASON;
}

bool Response::Status::exists(void) const { return (_exists); }

void Response::Status::reset(void)
{
	_statusCode = DEFAULT_STATUS_CODE;
	_reason = DEFAULT_REASON;
	_exists = false;
}

Response::Location::Location(void) : uri(), query() {}

void Response::Location::reset(void)
{
	uri.clear();
	query.clear();
}

Response::Response(void)
	: _status(), _headers(), _hasContentLength(false), _contentLength(0), _body(BODY_NAME_TEMPLATE)
{}

unsigned short	   Response::getStatusCode(void) const { return (_status.getStatusCode()); }
std::string const &Response::getStatusReason(void) const { return (_status.getReason()); }
std::size_t		   Response::getHeadersSize(void) const { return (_headers.size()); }
std::map<std::string, std::string> const &Response::getHeaders(void) const { return (_headers); }
std::string const						 &Response::getHeader(std::string const &key) const
{
	std::map<std::string, std::string>::const_iterator itValue = _headers.find(key);
	if (itValue == _headers.end())
	{
		static std::string const empty;
		return (empty);
	}
	return (itValue->second);
}
bool Response::hasHeader(std::string const &key) const
{
	return (_headers.find(key) != _headers.end());
}
std::string const		&Response::getLocationUri(void) const { return (_location.uri); }
std::string const		&Response::getLocationQuery(void) const { return (_location.query); }
Response::Location::Type Response::getLocationType(void) const { return (_location.type); }
bool					 Response::hasLocation(void) const { return (!_location.uri.empty()); }
std::size_t				 Response::getContentLength(void) const { return (_contentLength); }
bool					 Response::hasContentLength(void) const { return (_hasContentLength); }
Response::Type			 Response::getType(void) const { return (_type); }
int						 Response::getBodyFd(void) const { return (_body.getFd()); }

void Response::setStatus(unsigned short statusCode, std::string const &reason)
{
	_status.setStatus(statusCode, reason);
}

void Response::setDefaultRedirStatus(void) { _status.setDefaultRedirStatus(); }

void Response::setHeader(std::string const &key, std::string const &value)
{
	_headers[key] = value;
}

void Response::setLocation(std::string const &uri, std::string const &query, Location::Type type)
{
	_location.uri = uri;
	_location.query = query;
	_location.type = type;
}

void Response::setContentLength(std::size_t contentLength)
{
	_hasContentLength = true;
	_contentLength = contentLength;
}

void Response::setType(Type type) { _type = type; }

std::size_t Response::appendBody(std::vector<char> const &buf) { return (_body.write(buf)); }

std::size_t Response::appendBody(std::vector<char> const &buf, std::size_t size)
{
	return (_body.write(buf, size));
}

void Response::prepareForReading(void)
{
	if (_body.exists())
		_body.resetPosition();
}

void Response::reset(void)
{
	_status.reset();
	_headers.clear();
	_location.reset();
	_contentLength = 0;
	_hasContentLength = false;
	_body.reset();
}
} // namespace cgi