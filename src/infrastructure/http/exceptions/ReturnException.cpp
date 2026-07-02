/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReturnException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 02:05:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 02:12:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/exceptions/ReturnException.hpp"

namespace http {
ReturnException::ReturnException(std::string const &message, int const statusCode) throw()
	: _message(message), _statusCode(statusCode)
{}
ReturnException::ReturnException(int const statusCode) throw()
	: _message("httpReturnException"), _statusCode(statusCode)
{}
char const *ReturnException::what(void) const throw() { return (_message.c_str()); }

unsigned short ReturnException::getStatusCode(void) const throw() { return (_statusCode); }

} // namespace http