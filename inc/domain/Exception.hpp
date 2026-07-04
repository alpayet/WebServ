/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:34:45 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:34:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOMAINEXCEPTION_HPP
#define DOMAINEXCEPTION_HPP

#include <exception>
#include <string>

namespace domain {
class Exception : public std::exception
{
  public:
	enum ErrorCode
	{
		pathMissing,
		typeUnsupported
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
} // namespace domain

#endif // DOMAINEXCEPTION_HPP
