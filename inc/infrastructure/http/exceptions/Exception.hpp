/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 22:11:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 02:09:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPEXCEPTION_HPP
#define HTTPEXCEPTION_HPP

#include <exception>
#include <string>

namespace http {
class Exception : public std::exception
{
  public:
	enum ErrorCode
	{
		invalidLineBreak,
		requestLineMalformed,
		headerLineMalformed,
		methodInvalid,
		methodNotAllowed,
		targetInvalid,
		versionInvalid,
		headerKeyInvalid,
		headerValueInvalid,
		contentLengthInvalid,
		contentLengthRequired,
		requestLineTooLarge,
		headerLineTooLarge,
		headerCountTooLarge,
		bodyTooLarge
	};

  public:
	Exception(std::string const &message, ErrorCode const internalCode) throw();
	Exception(ErrorCode const internalCode) throw();

	virtual ~Exception(void) throw() {}

	virtual char const *what(void) const throw();

	ErrorCode getErrorCode(void) const throw();

  private:
	std::string _message;
	ErrorCode	_internalCode;
};
} // namespace http

#endif // HTTPEXCEPTION_HPP