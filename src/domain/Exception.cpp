/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:38:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:13:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/Exception.hpp"

namespace domain {
Exception::Exception(std::string const &message, ErrorCode const internalCode) throw()
	: _message(message), _internalCode(internalCode)
{}

Exception::Exception(ErrorCode const internalCode) throw()
	: _message("domainException"), _internalCode(internalCode)
{}

Exception::ErrorCode Exception::getErrorCode(void) const { return (_internalCode); }

char const *Exception::what(void) const throw() { return (_message.c_str()); }

} // namespace domain
