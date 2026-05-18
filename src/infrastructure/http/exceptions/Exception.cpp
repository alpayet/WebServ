/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:04:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/18 20:24:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/exceptions/Exception.hpp"

Http::Exception::Exception(std::string const &message,
	ErrorCode const internalCode) throw() :
	_message(message),
	_internalCode(internalCode)
{}

Http::Exception::Exception(ErrorCode const internalCode) throw() :
	_message("HttpException"),
	_internalCode(internalCode)
{}

Http::Exception::ErrorCode	Http::Exception::getErrorCode(void) const
{
	return (this->_internalCode);
}

char const	*Http::Exception::what(void) const throw()
{
	return (this->_message.c_str());
}


