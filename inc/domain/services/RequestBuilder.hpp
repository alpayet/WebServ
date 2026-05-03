/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBuilder.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 01:41:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 01:55:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBUILDER_HPP
# define REQUESTBUILDER_HPP

#include <string>
#include <map>

class RequestBuilder
{
	public:
		RequestBuilder(void);

		void	withTarget(std::string const &target);
		void	withProtocol(std::string const &protocol);
		void	withHeaders(std::map<std::string, std::string> const &headers);

	private:
		RequestBuilder(RequestBuilder const &src);
		RequestBuilder	&operator=(RequestBuilder const &rhs);

		std::string							_target;
		std::string							_protocol;
		std::map<std::string, std::string>	_headers;
};

#endif