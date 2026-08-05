/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 01:52:58 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:21:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIEXCEPTION_HPP
#define CGIEXCEPTION_HPP

#include <exception>
#include <string>

namespace cgi {
class Exception : public std::exception
{
  public:
	enum ErrorCode
	{
		PIPE_FAILED,
		FORK_FAILED,
		DOC_RESPONSE_MALFORMED,
		LOCAL_REDIR_RESPONSE_MALFORMED,
		CLIENT_REDIR_RESPONSE_MALFORMED,
		CLIENT_REDIR_DOC_RESPONSE_MALFORMED,
		STATUS_CODE_INVALID,
		STATUS_REASON_INVALID,
		LOCATION_INVALID,
		LINE_BREAK_INVALID,
		HEADER_LINE_MALFORMED,
		HEADER_KEY_INVALID,
		HEADER_VALUE_INVALID,
		CONTENT_LENGTH_INVALID,
		HEADER_LINE_TOO_LARGE,
		HEADER_COUNT_TOO_LARGE,
		BODY_TOO_LARGE,
		BODY_SIZE_MISMATCH,
		TIMEOUT,
		PREMATURE_EOF
	};

  public:
	Exception(std::string const &message, ErrorCode internalCode) throw();
	Exception(ErrorCode internalCode) throw();
	virtual ~Exception(void) throw() {}

	ErrorCode getErrorCode(void) const throw();

	virtual char const *what(void) const throw();

  private:
	std::string _message;
	ErrorCode	_internalCode;
};
} // namespace cgi

#endif // CGIEXCEPTION_HPP
