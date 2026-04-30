/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:44:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/30 19:58:07 by alpayet          ###   ########.fr       */
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
		HttpRequest(MethodType const method, std::string const &target,
			std::string const &protocol, std::map<std::string, std::string> const &headers);
		HttpRequest(HttpRequest const &src);
		virtual ~HttpRequest(void) {}

		HttpRequest	&operator=(HttpRequest const &rhs);

		virtual MethodType			getMethod(void) const;
		virtual std::string const	&getTarget(void) const;
		virtual std::string const	&getProtocol(void) const;

		virtual IRequest	*clone(void) const;

	private:
		MethodType	_method;
		std::string	_target;
		std::string	_protocol;
};

#endif