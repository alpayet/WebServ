/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/03 19:27:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
# define HTTPREQUESTPARSER_HPP

# include "shared/RequestDto.hpp"
# include <string>
# include <vector>
# include <map>

class IRequestInputPort;

class HttpRequestParser
{
	public:
		enum ParseState
		{
			StartLine,
			Header,
			Body,
			Complete
		};

	public:
		HttpRequestParser(IRequestInputPort *requestInputPort);

		ParseState									getState(void) const;
		// IRequest::MethodType						getMethod(void) const;
		// std::string const							&getTarget(void) const;
		// std::string const							&getProtocol(void) const;
		// std::map<std::string, std::string> const	&getHeaders(void) const;

		ParseState	parse(std::vector<char> const &readBuf);

	private:
		IRequestInputPort	*_requestInputPort;
		RequestDto			_requestDto;

		std::size_t	_pos;
		ParseState	_state;

		void	parseStartLine(std::vector<char>::const_iterator itStart,
			std::vector<char>::const_iterator itLineEnd);
		void	parseHeaderLine(std::vector<char>::const_iterator itStart,
			std::vector<char>::const_iterator itLineEnd);
};

#endif