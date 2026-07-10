/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:04:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:33:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/exceptions/Exception.hpp"

namespace http {
Exception::Exception(std::string const &message, ErrorCode internalCode) throw()
	: _message(message), _internalCode(internalCode)
{}

Exception::Exception(ErrorCode internalCode) throw()
	: _message("httpException"), _internalCode(internalCode)
{}

Exception::ErrorCode Exception::getErrorCode(void) const throw() { return (_internalCode); }

char const *Exception::what(void) const throw() { return (_message.c_str()); }

} // namespace http
