/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 01:52:58 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/07 00:36:06 by alpayet          ###   ########.fr       */
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
		localRedirResponseMalformed,
		clientRedirResponseMalformed,
		lineBreakInvalid,
		headerLineMalformed,
		headerKeyInvalid,
		headerValueInvalid,
		contentLengthInvalid,
		headerLineTooLarge,
		headerCountTooLarge,
		bodyTooLarge,
		timeOut
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
