/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:49:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 23:14:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "infrastructure/storage/file_system/TempWriter.hpp"
#include <map>
#include <string>

namespace http {

class Request
{
  public:
	class StartLine
	{
	  public:
		std::string method;
		std::string target;
		std::string query;
		std::string protocol;

		void reset(void);
	};

  public:
	Request(void);

	StartLine						   startLine;
	std::map<std::string, std::string> headers;
	std::size_t						   contentLength;
	fileSystem::TempWriter			   body;

	static char const BODY_NAME_TEMPLATE[];

	void reset(void);

  private:
	Request(Request const &src);
	Request &operator=(Request const &rhs);
};
} // namespace http

#endif // HTTPREQUEST_HPP