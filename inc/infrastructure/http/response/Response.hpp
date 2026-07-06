/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:47:49 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 00:51:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "application/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
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

	class StatusLine
	{
	  public:
		StatusLine(void);

		unsigned short statusCode;
		std::string	   reason;

		void reset(void);

		static unsigned short const DEFAULT_STATUS_CODE;
		static char const			DEFAULT_REASON[];
	};
	struct Header
	{
		std::string key;
		std::string value;
	};

  public:
	Response(void);

	StatusLine			statusLine;
	std::vector<Header> headers;
	std::size_t			contentLength;
	std::vector<char>	body;

	void reset(void);

	static Response
	buildErrorPage(unsigned short StatusErrorCode, app::SystemResourceInfo const &errorPageInfo);

	static Response buildDefault(unsigned short statusCode);
};

class Response::Builder
{
  public:
	Builder	 &withStatusCode(unsigned short statusCode);
	Builder	 &withStatusReason(std::string const &reason);
	Builder	 &withStatusLine(unsigned short statusCode);
	Builder	 &withContentLength(std::size_t contentLength);
	Builder	 &withContentLength(std::string const &contentLength);
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