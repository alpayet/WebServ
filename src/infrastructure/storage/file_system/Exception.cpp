/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 03:42:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:15:27 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Exception.hpp"

namespace fileSystem {
Exception::Exception(std::string const &message, ErrorCode const internalCode) throw()
	: _message(message), _internalCode(internalCode)
{}

Exception::Exception(ErrorCode const internalCode) throw()
	: _message("fileSystemException"), _internalCode(internalCode)
{}

Exception::ErrorCode Exception::getErrorCode(void) const { return (_internalCode); }

char const *Exception::what(void) const throw() { return (_message.c_str()); }
} // namespace fileSystem