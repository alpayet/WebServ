/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:49:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:17:17 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "infrastructure/storage/file_system/TempWriter.hpp"
#include <map>
#include <ostream>
#include <string>

namespace webserv {
namespace http {

class Request
{
  private:
	struct StartLine
	{
		std::string method;
		std::string target;
		std::string query;
		std::string protocol;

		void reset(void);
	};

  public:
	Request(void);

	std::string const						 &getMethod(void) const;
	std::string const						 &getTarget(void) const;
	std::string const						 &getQuery(void) const;
	bool									  hasQuery(void) const;
	std::string const						 &getProtocol(void) const;
	std::map<std::string, std::string> const &getHeaders(void) const;
	std::string const						 &getHeader(std::string const &key) const;
	bool									  hasHeader(std::string const &key) const;
	std::size_t								  getContentLength(void) const;
	bool									  hasContentLength(void) const;
	std::string const						 &getConnection(void) const;
	std::string const						 &getBodyPath(void) const;
	bool									  hasBody(void) const;

	void
	setStartLine(std::string const &method, std::string const &target, std::string const &protocol);
	void setStartLine(
		std::string const &method,
		std::string const &target,
		std::string const &query,
		std::string const &protocol
	);
	void setTarget(std::string const &target);
	void setQuery(std::string const &query);
	void setHeader(std::string const &key, std::string const &value);
	void setContentLength(std::size_t contentLength);

	std::size_t appendBody(std::vector<char> const &buf);
	std::size_t appendBody(std::vector<char> const &buf, std::size_t size);

	void prepareForReading(void);

	void reset(void);

  private:
	Request(Request const &src);
	Request &operator=(Request const &rhs);

	StartLine						   _startLine;
	std::map<std::string, std::string> _headers;
	bool							   _hasContentLength;
	std::size_t						   _contentLength;
	fileSystem::TempWriter			   _body;

	static char const BODY_NAME_TEMPLATE[];
};

std::ostream &operator<<(std::ostream &lhs, Request const &rhs);

} // namespace http
} // namespace webserv

#endif // HTTPREQUEST_HPP