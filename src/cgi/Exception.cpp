/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 01:55:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 01:56:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Exception.hpp"

namespace cgi {
Exception::Exception(std::string const &message, ErrorCode internalCode) throw()
	: _message(message), _internalCode(internalCode)
{}

Exception::Exception(ErrorCode internalCode) throw()
	: _message("cgiException"), _internalCode(internalCode)
{}

Exception::ErrorCode Exception::getErrorCode(void) const throw() { return (_internalCode); }

char const *Exception::what(void) const throw() { return (_message.c_str()); }

} // namespace cgi