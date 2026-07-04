/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReturnException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 02:03:39 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:32:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RETURNEXCEPTION_HPP
#define RETURNEXCEPTION_HPP

#include <exception>
#include <string>

namespace http {
class ReturnException : public std::exception
{
  public:
	ReturnException(std::string const &message, int statusCode) throw();
	ReturnException(int statusCode) throw();

	virtual ~ReturnException(void) throw() {}

	virtual char const *what(void) const throw();

	unsigned short getStatusCode(void) const throw();

  private:
	std::string	   _message;
	unsigned short _statusCode;
};
} // namespace http

#endif // RETURNEXCEPTION_HPP