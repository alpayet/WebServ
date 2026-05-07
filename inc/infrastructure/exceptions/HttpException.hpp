/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 22:11:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/07 19:38:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPEXCEPTION_HPP
# define HTTPEXCEPTION_HPP

# include <exception>
# include <string>

class HttpException : public std::exception
{
	public:
		enum ErrorCode
		{
			invalidLineBreak,
			malformedStartLine,
			invalidMethod,
			invalidTarget,
			invalidVersion,
			invalidHeaderKey,
			invalidHeaderValue,
			payloadTooLarge
		};

	public:
		HttpException(std::string const &message, ErrorCode const internalCode) throw();
		HttpException(ErrorCode const internalCode) throw();
		virtual		~HttpException(void) throw() {}

		ErrorCode	getErrorCode(void) const;

		virtual char const	*what(void) const throw();

	private:
		std::string	_message;
		ErrorCode	_internalCode;
};

#endif