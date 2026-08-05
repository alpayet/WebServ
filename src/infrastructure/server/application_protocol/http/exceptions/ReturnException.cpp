/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReturnException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 02:05:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:55:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/exceptions/ReturnException.hpp"

namespace http {
ReturnException::ReturnException(std::string const &message, int statusCode) throw()
	: _message(message), _statusCode(statusCode)
{}
ReturnException::ReturnException(int statusCode) throw()
	: _message("httpReturnException"), _statusCode(statusCode)
{}
char const *ReturnException::what(void) const throw() { return (_message.c_str()); }

unsigned short ReturnException::getStatusCode(void) const throw() { return (_statusCode); }

} // namespace http