/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:04:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/22 20:05:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/exceptions/Exception.hpp"

namespace http
{
	Exception::Exception(std::string const &message,
		ErrorCode const internalCode) throw() :
		_message(message),
		_internalCode(internalCode)
	{}

	Exception::Exception(ErrorCode const internalCode) throw() :
		_message("HttpException"),
		_internalCode(internalCode)
	{}

	Exception::ErrorCode	Exception::getErrorCode(void) const
	{
		return (this->_internalCode);
	}

	char const	*Exception::what(void) const throw()
	{
		return (this->_message.c_str());
	}
}


