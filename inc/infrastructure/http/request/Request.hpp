/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:49:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 03:30:23 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "BodyFile.hpp"
#include <map>
#include <string>

namespace http {
namespace request {

struct Request
{
	Request(void) : contentLength(0) {}

	std::map<std::string, std::string> headers;
	std::string						   method;
	std::string						   target;
	std::string						   protocol;
	std::string						   query;
	size_t							   contentLength;
	BodyFile						   body;
};
} // namespace request
} // namespace http

#endif // HTTPREQUEST_HPP