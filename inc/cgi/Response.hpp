/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:33:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/05 01:48:24 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
#define CGIRESPONSE_HPP

#include <map>
#include <string>

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
		static char const			REASON[];

		void reset(void);
	};

  public:
	Response(void);

	StatusLine						   statusLine;
	std::map<std::string, std::string> headers;
	std::string						   location;
	std::size_t						   contentLength;
	Type							   type;

	void reset(void);

  private:
	Response(Response const &src);
	Response &operator=(Response const &rhs);
};
} // namespace cgi

#endif // CGIRESPONSE_HPP