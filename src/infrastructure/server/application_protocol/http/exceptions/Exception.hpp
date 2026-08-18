/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 22:11:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/18 18:40:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPEXCEPTION_HPP
#define HTTPEXCEPTION_HPP

#include <exception>
#include <string>

namespace webserv {
namespace http {
class Exception : public std::exception
{
  public:
	enum ErrorCode
	{
		LINE_BREAK_INVALID,
		REQUEST_LINE_MALFORMED,
		HEADER_LINE_MALFORMED,
		METHOD_INVALID,
		METHOD_NOT_ALLOWED,
		METHOD_UNSUPPORTED,
		TARGET_INVALID,
		VERSION_INVALID,
		HEADER_KEY_INVALID,
		HEADER_VALUE_INVALID,
		CONTENT_LENGTH_INVALID,
		CONTENT_LENGTH_REQUIRED,
		REQUEST_LINE_TOO_LARGE,
		HEADER_LINE_TOO_LARGE,
		HEADER_COUNT_TOO_LARGE,
		BODY_TOO_LARGE,
		MATCH_ROUTE_FAILED,
		MAX_LOCAL_REDIR_DEPTH_EXCEEDED,
		TIMEOUT
	};

  public:
	Exception(char const *message, ErrorCode internalCode) throw();
	Exception(ErrorCode internalCode) throw();

	virtual ~Exception(void) throw() {}

	virtual char const *what(void) const throw();

	ErrorCode getErrorCode(void) const throw();

  private:
	char const *_message;
	ErrorCode	_internalCode;
};
} // namespace http
} // namespace webserv

#endif // HTTPEXCEPTION_HPP