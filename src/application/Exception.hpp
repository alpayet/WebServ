/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:34:45 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:38:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPEXCEPTION_HPP
#define APPEXCEPTION_HPP

#include <exception>
#include <string>

namespace webserv {
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
	Exception(char const *message, ErrorCode internalCode) throw();
	Exception(ErrorCode internalCode) throw();
	virtual ~Exception(void) throw() {}

	ErrorCode getErrorCode(void) const throw();

	virtual char const *what(void) const throw();

  private:
	char const *_message;
	ErrorCode	_internalCode;
};
} // namespace app
} // namespace webserv

#endif // APPEXCEPTION_HPP
