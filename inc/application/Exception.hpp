/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:34:45 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 22:34:54 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPEXCEPTION_HPP
#define APPEXCEPTION_HPP

#include <exception>
#include <string>

namespace app {
class Exception : public std::exception
{
  public:
	enum ErrorCode
	{
		accessDenied,
		notFound,
		listingDisabled
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
} // namespace app

#endif // APPEXCEPTION_HPP
