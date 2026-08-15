/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:38:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:38:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/Exception.hpp"

namespace webserv {
namespace app {
Exception::Exception(char const *message, ErrorCode internalCode) throw()
	: _message(message), _internalCode(internalCode)
{}

Exception::Exception(ErrorCode internalCode) throw()
	: _message("appException"), _internalCode(internalCode)
{}

Exception::ErrorCode Exception::getErrorCode(void) const throw() { return (_internalCode); }

char const *Exception::what(void) const throw() { return (_message); }

} // namespace app
} // namespace webserv
