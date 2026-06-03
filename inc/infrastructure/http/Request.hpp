/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:49:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/03 22:04:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "BodyFile.hpp"
#include <map>
#include <string>

namespace http
{
	struct Request
	{
		Request(void) : contentLength(0) {}

		std::map<std::string, std::string> headers;
		std::string						   method;
		std::string						   target;
		std::string						   protocol;
		size_t							   contentLength;
		BodyFile						   body;
	};
} // namespace http

#endif // HTTPREQUEST_HPP