/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:04:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/05 20:46:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/exceptions/HttpException.hpp"

HttpException::HttpException(std::string const &message,
	ErrorCode const internalCode) throw() :
	_message(message),
	_internalCode(internalCode)
{}

HttpException::HttpException(ErrorCode const internalCode) throw() :
	_message("HttpException"),
	_internalCode(internalCode)
{}

HttpException::ErrorCode	HttpException::getErrorCode(void) const
{
	return (this->_internalCode);
}

char const	*HttpException::what(void) const throw()
{
	return (this->_message.c_str());
}


