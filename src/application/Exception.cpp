/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:38:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:36:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/Exception.hpp"

namespace app {
Exception::Exception(std::string const &message, ErrorCode internalCode) throw()
	: _message(message), _internalCode(internalCode)
{}

Exception::Exception(ErrorCode internalCode) throw()
	: _message("appException"), _internalCode(internalCode)
{}

Exception::ErrorCode Exception::getErrorCode(void) const throw() { return (_internalCode); }

char const *Exception::what(void) const throw() { return (_message.c_str()); }

} // namespace app
