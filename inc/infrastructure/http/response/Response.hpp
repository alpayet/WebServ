/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:47:49 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 22:46:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "application/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include <map>
#include <string>
#include <vector>

namespace app {
struct SystemResourceInfo;
} // namespace app

namespace http {

class IErrorPagesProvider;

class Response
{
  public:
	class Builder;

  private:
	struct StatusLine
	{
		StatusLine(void);

		unsigned short statusCode;
		std::string	   reason;

		void reset(void);

		static unsigned short const DEFAULT_STATUS_CODE;
		static char const			DEFAULT_REASON[];
	};

  public:
	struct Header
	{
		std::string key;
		std::string value;
	};

  public:
	Response(void);

	unsigned short			   getStatusCode(void) const;
	std::string const		  &getStatusReason(void) const;
	std::vector<Header> const &getHeaders(void) const;
	std::size_t				   getContentLength(void) const;
	std::vector<char> const	  &getBody(void) const;
	bool					   hasBody(void) const;

	void reset(void);

	static Response
	buildErrorPage(unsigned short StatusErrorCode, app::SystemResourceInfo const &errorPageInfo);
	static Response buildDefault(unsigned short statusCode);

  private:
	StatusLine			_statusLine;
	std::vector<Header> _headers;
	std::size_t			_contentLength;
	std::vector<char>	_body;
};

class Response::Builder
{
  public:
	Builder	 &withStatusCode(unsigned short statusCode);
	Builder	 &withStatusReason(std::string const &reason);
	Builder	 &withStatusLine(unsigned short statusCode);
	Builder	 &withContentLength(std::size_t contentLength);
	Builder	 &withContentLength(std::string const &contentLength);
	Builder	 &withHeaders(std::map<std::string, std::string> const &headers);
	Builder	 &withHeader(std::string const &key, std::string const &value);
	Builder	 &withHeader(std::string const &key, std::size_t value);
	Builder	 &withBody(std::vector<char> const &body);
	Builder	 &withBody(std::string const &body);
	Builder	 &withBody(char const *body);
	Response &build(void);

  private:
	Response _response;
};
} // namespace http

#endif // HTTPRESPONSE_HPP