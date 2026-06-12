/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:34:45 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:12:55 by alpayet          ###   ########.fr       */
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
		PathTraversalDetected,
	};

  public:
	Exception(std::string const &message, ErrorCode const internalCode) throw();
	Exception(ErrorCode const internalCode) throw();
	virtual ~Exception(void) throw() {}

	ErrorCode getErrorCode(void) const;

	virtual char const *what(void) const throw();

  private:
	std::string _message;
	ErrorCode	_internalCode;
};
} // namespace domain

#endif // DOMAINEXCEPTION_HPP
