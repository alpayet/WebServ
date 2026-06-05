/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataSourcesException.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 19:26:51 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/data_sources/DataSourcesException.hpp"

DataSourcesException::DataSourcesException(
	std::string const &message, ErrorCode const internalCode
) throw()
	: _message(message), _internalCode(internalCode)
{
}

DataSourcesException::DataSourcesException(ErrorCode const internalCode) throw()
	: _message("DataSourcesException"), _internalCode(internalCode)
{
}

DataSourcesException::ErrorCode DataSourcesException::getErrorCode(void) const
{
	return (_internalCode);
}

char const *DataSourcesException::what(void) const throw() { return (_message.c_str()); }