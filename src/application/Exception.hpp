/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:34:45 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:16:21 by alpayet          ###   ########.fr       */
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
		ACCESS_DENIED,
		NOT_FOUND,
		LISTING_DISABLED,
		DELETE_FAILED,
		PATH_TRAVERSAL_DETECTED,
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
} // namespace app

#endif // APPEXCEPTION_HPP
