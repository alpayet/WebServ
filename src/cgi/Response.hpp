/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:33:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/11 20:34:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
#define CGIRESPONSE_HPP

#include "infrastructure/storage/file_system/TempWriter.hpp"
#include <map>
#include <string>
#include <vector>

namespace cgi {
class Response
{
  public:
	enum Type
	{
		document,
		localRedir,
		clientRedir,
		clientRedirDoc
	};

  private:
	class Status
	{
	  public:
		Status(void);

		unsigned short	   getStatusCode(void) const;
		std::string const &getReason(void) const;

		void setStatus(unsigned statusCode, std::string const &reason);
		void setDefaultRedirStatus(void);
		bool exists(void) const;
		void reset(void);

	  private:
		unsigned short _statusCode;
		std::string	   _reason;
		bool		   _exists;

		static unsigned short const DEFAULT_STATUS_CODE;
		static char const			DEFAULT_REASON[];
		static unsigned short const DEFAULT_REDIR_STATUS_CODE;
		static char const			DEFAULT_REDIR_REASON[];
	};

  public:
	struct Location
	{
		enum Type
		{
			local,
			client
		};

		Location(void);

		std::string uri;
		std::string query;
		Type		type;

		void reset(void);
	};

  public:
	Response(void);

	unsigned short							  getStatusCode(void) const;
	std::string const						 &getStatusReason(void) const;
	bool									  hasStatus(void) const;
	std::size_t								  getHeadersSize(void) const;
	std::map<std::string, std::string> const &getHeaders(void) const;
	std::string const						 &getHeader(std::string const &key) const;
	bool									  hasHeader(std::string const &key) const;
	std::vector<std::string> const			 &getCookies(void) const;
	std::string const						 &getLocationUri(void) const;
	std::string const						 &getLocationQuery(void) const;
	Location::Type							  getLocationType(void) const;
	bool									  hasLocation(void) const;
	std::size_t								  getContentLength(void) const;
	bool									  hasContentLength(void) const;
	Type									  getType(void) const;
	int										  getBodyFd(void) const;

	void setStatus(unsigned short statusCode, std::string const &reason);
	void setDefaultRedirStatus();
	void setHeader(std::string const &key, std::string const &value);
	void setCookie(std::string const &value);
	void setLocation(std::string const &uri, std::string const &query, Location::Type type);
	void setContentLength(std::size_t contentLength);
	void setType(Type type);

	std::size_t appendBody(std::vector<char> const &buf);
	std::size_t appendBody(std::vector<char> const &buf, std::size_t size);

	void prepareForReading(void);

	void reset(void);

  private:
	Response(Response const &src);
	Response &operator=(Response const &rhs);

	Status							   _status;
	std::map<std::string, std::string> _headers;
	std::vector<std::string>		   _cookies;
	Location						   _location;
	bool							   _hasContentLength;
	std::size_t						   _contentLength;
	fileSystem::TempWriter			   _body;
	Type							   _type;

	static char const BODY_NAME_TEMPLATE[];
};

std::ostream &operator<<(std::ostream &lhs, Response const &rhs);

} // namespace cgi

#endif // CGIRESPONSE_HPP