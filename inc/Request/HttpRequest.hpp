/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:44:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/28 21:34:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "IRequest.hpp"
# include "HttpMessage.hpp"
# include <vector>

class HttpRequest : public IRequest, public HttpMessage
{
	public:
		enum MethodType
		{
			MethodType_Get,
			MethodType_Post,
			MethodType_Delete
		};

	public:
		HttpRequest(void);
		HttpRequest(HttpRequest const &src);
		virtual ~HttpRequest(void);

		HttpRequest	&operator=(HttpRequest const &rhs);

		virtual ParseState	parse(std::vector<char> const &readBuf);

	private:
		MethodType	_method;
		std::string	_target;
		std::string	_protocol;
		std::size_t	_pos;
		ParseState	_state;

		void	parseStartLine(std::vector<char>::const_iterator it_start,
			std::vector<char>::const_iterator it_line_end);
		void	parseHeaderLine(std::vector<char>::const_iterator it_start,
			std::vector<char>::const_iterator it_line_end);


};

#endif