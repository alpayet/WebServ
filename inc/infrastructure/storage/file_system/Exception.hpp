/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 03:42:35 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 03:34:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMEXCEPTION_HPP
#define FILESYSTEMEXCEPTION_HPP

#include <exception>
#include <string>

namespace fileSystem {
class Exception : public std::exception
{
  public:
	enum ErrorCode
	{
		fileOpenFailed,
		fileCloseFailed,
		fileRemoveFailed,
		fileWriteFailed,
		fileReadFailed,
		fileTruncateFailed,
		fileLseekFailed,
		fileNotFound,
		permissionDenied
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

} // namespace fileSystem

#endif // FILESYSTEMEXCEPTION_HPP