/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 22:11:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 04:07:01 by alpayet          ###   ########.fr       */
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
	// TODO: faire une surcharge du construteur qui prend un int en param pour pouvoir throw
	// nimporte laquelle error code
	virtual ~Exception(void) throw() {}
	virtual char const *what(void) const throw();

	ErrorCode getErrorCode(void) const;

  private:
	std::string _message;
	ErrorCode	_internalCode;
};
} // namespace http

#endif // HTTPEXCEPTION_HPP