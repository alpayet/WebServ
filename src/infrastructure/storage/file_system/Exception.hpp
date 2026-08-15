/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 03:42:35 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:23:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMEXCEPTION_HPP
#define FILESYSTEMEXCEPTION_HPP

#include <exception>
#include <string>

namespace webserv {
namespace fileSystem {
class Exception : public std::exception
{
  public:
	enum ErrorCode
	{
		OPEN_FAILED,
		WRITE_FAILED,
		READ_FAILED,
		TRUNCATE_FAILED,
		LSEEK_FAILED
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

} // namespace fileSystem
} // namespace webserv

#endif // FILESYSTEMEXCEPTION_HPP