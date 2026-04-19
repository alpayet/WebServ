/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:44:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/19 22:53:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "IRequest.hpp"
# include "HttpMessage.hpp"

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

		virtual ParseState	parse() {}

	private:
		MethodType	_method;
		std::string	_target;
		std::string	_protocol;
};

#endif