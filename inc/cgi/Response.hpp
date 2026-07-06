/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:33:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/07 00:30:55 by alpayet          ###   ########.fr       */
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

	class StatusLine
	{
	  public:
		StatusLine(void);

		unsigned short statusCode;
		std::string	   reason;
		bool		   exists;

		static unsigned short const DEFAULT_STATUS_CODE;
		static char const			DEFAULT_REASON[];

		void reset(void);
	};

	class Location
	{
	  public:
		enum Type
		{
			local,
			client
		};

	  public:
		Location(void);

		std::string uri;
		Type		type;
		bool		exists;

		void reset(void);
	};

  public:
	Response(void);

	StatusLine						   statusLine;
	std::map<std::string, std::string> headers;
	Location						   location;
	ssize_t							   contentLength;
	fileSystem::TempWriter			   body;
	Type							   type;

	static char const BODY_NAME_TEMPLATE[];

	void reset(void);

  private:
	Response(Response const &src);
	Response &operator=(Response const &rhs);
};
} // namespace cgi

#endif // CGIRESPONSE_HPP