/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:50:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/29 02:41:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Router.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"

namespace http
{
	Router::Router(void) {}

	Router::Router(const Router &src) { *this = src; }

	Router::~Router(void) {}

	Router &Router::operator=(Router const &rhs)
	{
		if (this != &rhs)
		{
			//
		}
		return (*this);
	}

	void Router::route(const http::Request &request, http::Response &response)
	{
		// TODO: faire une methode "const Location& findLocation(std::string const &uri) const;"
		// TODO: faire egalement une methode "bool ismethodAllowed(std::string const &method)
		// cosnt;" de Location if(location.ismethodAllowed()) throw
		// Exception(Exception::methodNotAllowed);
	}
} // namespace http
