/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:49:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/24 23:10:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <map>
#include <string>

namespace http
{
	struct Request
	{
		std::string						   method;
		std::string						   target;
		std::string						   protocol;
		std::map<std::string, std::string> headers;
	};
} // namespace http

#endif // HTTPREQUEST_HPP