/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataSourcesException.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 19:24:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASOURCESEXCEPTION_HPP
#define DATASOURCESEXCEPTION_HPP

#include <exception>
#include <string>

class DataSourcesException : public std::exception
{
  public:
	enum ErrorCode
	{
		fileOpenFailed,
	};

  public:
	DataSourcesException(std::string const &message, ErrorCode const internalCode) throw();
	DataSourcesException(ErrorCode const internalCode) throw();
	virtual ~DataSourcesException(void) throw() {}

	ErrorCode getErrorCode(void) const;

	virtual char const *what(void) const throw();

  private:
	std::string _message;
	ErrorCode	_internalCode;
};

#endif // DATASOURCESEXCEPTION_HPP