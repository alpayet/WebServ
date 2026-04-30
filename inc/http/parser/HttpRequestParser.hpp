/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/30 21:21:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
# define HTTPREQUESTPARSER_HPP

# include <string>
# include <vector>
# include <map>

enum IRequest::MethodType;

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
		HttpRequestParser(void);
		HttpRequestParser(HttpRequestParser const &src);
		~HttpRequestParser(void) {}

		HttpRequestParser	&operator=(HttpRequestParser const &rhs);

		ParseState									getState(void) const;
		IRequest::MethodType						getMethod(void) const;
		std::string const							&getTarget(void) const;
		std::string const							&getProtocol(void) const;
		std::map<std::string, std::string> const	&getHeaders(void) const;

		ParseState	parse(std::vector<char> const &readBuf);

	private:
		std::size_t	_pos;
		ParseState	_state;

		IRequest::MethodType				_method;
		std::string							_target;
		std::string							_protocol;
		std::map<std::string, std::string>	_headers;

		void	parseStartLine(std::vector<char>::const_iterator it_start,
			std::vector<char>::const_iterator it_line_end);
		void	parseHeaderLine(std::vector<char>::const_iterator it_start,
			std::vector<char>::const_iterator it_line_end);
};

#endif