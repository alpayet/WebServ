/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:26:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 02:38:03 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/Request.hpp"

namespace http {
char const Request::BODY_NAME_TEMPLATE[] = "http_request_body";

void Request::StartLine::reset(void)
{
	method.clear();
	target.clear();
	query.clear();
	protocol.clear();
}
Request::Request()
	: _headers(), _hasContentLength(false), _contentLength(0), _body(BODY_NAME_TEMPLATE)
{}

std::string const &Request::getMethod(void) const { return (_startLine.method); }
std::string const &Request::getTarget(void) const { return (_startLine.target); }
std::string const &Request::getQuery(void) const { return (_startLine.query); }
std::string const &Request::getProtocol(void) const { return (_startLine.protocol); }
std::map<std::string, std::string> const &Request::getHeaders(void) { return (_headers); }
std::string const						 &Request::getHeader(std::string const &key) const
{
	std::map<std::string, std::string>::const_iterator itValue = _headers.find(key);
	if (itValue == _headers.end())
	{
		static std::string const empty;
		return (empty);
	}
	return (itValue->second);
}
std::size_t Request::getContentLength(void) const { return (_contentLength); }
bool		Request::hasContentLength(void) const { return (_hasContentLength); }

void Request::setStartLine(
	std::string const &method, std::string const &target, std::string const &protocol
)
{
	_startLine.method = method;
	_startLine.target = target;
	_startLine.protocol = protocol;
}

void Request::setStartLine(
	std::string const &method,
	std::string const &target,
	std::string const &query,
	std::string const &protocol
)
{
	_startLine.method = method;
	_startLine.target = target;
	_startLine.query = query;
	_startLine.protocol = protocol;
}

void Request::setTarget(std::string const &target) { _startLine.target = target; }

void Request::setHeader(std::string const &key, std::string const &value) { _headers[key] = value; }

void Request::setContentLength(std::size_t contentLength)
{
	_hasContentLength = true;
	_contentLength = contentLength;
}

std::size_t Request::appendBody(std::vector<char> const &buf) { return (_body.write(buf)); }

std::size_t Request::appendBody(std::vector<char> const &buf, std::size_t size)
{
	return (_body.write(buf, size));
}

void Request::reset(void)
{
	_startLine.reset();
	_headers.clear();
	_hasContentLength = false;
	_contentLength = 0;
	_body.reset();
}

} // namespace http
