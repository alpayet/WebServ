/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 03:38:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:36:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Response.hpp"
#include "infrastructure/constants.hpp"

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
	: _status(), _headers(), _cookies(), _hasContentLength(false), _contentLength(0),
	  _body(BODY_NAME_TEMPLATE)
{}

unsigned short	   Response::getStatusCode(void) const { return (_status.getStatusCode()); }
std::string const &Response::getStatusReason(void) const { return (_status.getReason()); }
bool			   Response::hasStatus(void) const { return (_status.exists()); }
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
std::vector<std::string> const &Response::getCookies(void) const { return (_cookies); }

std::string const			   &Response::getLocationUri(void) const { return (_location.uri); }

std::string const			   &Response::getLocationQuery(void) const { return (_location.query); }

Response::Location::Type		Response::getLocationType(void) const { return (_location.type); }

bool		   Response::hasLocation(void) const { return (!_location.uri.empty()); }

std::size_t	   Response::getContentLength(void) const { return (_contentLength); }

bool		   Response::hasContentLength(void) const { return (_hasContentLength); }

Response::Type Response::getType(void) const { return (_type); }

int			   Response::getBodyFd(void) const { return (_body.getFd()); }

void Response::setStatus(unsigned short statusCode, std::string const &reason)
{
	_status.setStatus(statusCode, reason);
}

void Response::setDefaultRedirStatus(void) { _status.setDefaultRedirStatus(); }

void Response::setHeader(std::string const &key, std::string const &value)
{
	_headers[key] = value;
}

void Response::setCookie(std::string const &value) { _cookies.push_back(value); }

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
	_cookies.clear();
	_location.reset();
	_contentLength = 0;
	_hasContentLength = false;
	_body.reset();
}

std::ostream &operator<<(std::ostream &lhs, Response const &rhs)
{
	lhs << "***CGI RESPONSE***" << std::endl;

	lhs << "\tStatus:" << std::endl;
	lhs << "\t\tHasStatus:" << std::boolalpha << rhs.hasStatus() << std::endl;
	lhs << "\t\tStatusCode:" << rhs.getStatusCode() << std::endl;
	lhs << "\t\tReason:" << rhs.getStatusReason() << std::endl;

	lhs << "\tHeaders:" << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = rhs.getHeaders().begin();
		 it != rhs.getHeaders().end(); ++it)
		lhs << "\t\t" << it->first << ':' << it->second << std::endl;

	lhs << "\tCookies:" << std::endl;
	for (std::vector<std::string>::const_iterator it = rhs.getCookies().begin();
		 it != rhs.getCookies().end(); ++it)
		lhs << "\t\t" << headers::SET_COOKIE << ':' << *it << std::endl;

	lhs << "\tLocation:" << std::endl;
	lhs << "\t\tUri:" << rhs.getLocationUri() << std::endl;
	lhs << "\t\tQuery:" << rhs.getLocationQuery() << std::endl;
	lhs << "\t\tType:" << rhs.getLocationType() << std::endl;

	lhs << "\tHasContentLength:" << std::boolalpha << rhs.hasContentLength() << std::endl;
	lhs << "\tContentLength:" << rhs.getContentLength() << std::endl;

	lhs << "\tType:" << rhs.getType() << std::endl;

	lhs << "***END CGI RESPONSE***" << std::endl;
	return (lhs);
}
} // namespace cgi