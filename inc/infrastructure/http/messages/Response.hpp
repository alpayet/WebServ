/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:47:49 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 23:31:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>
#include <vector>

namespace http {
struct Response
{
	struct Status
	{
		unsigned short statusCode;
		std::string	   reason;
	};
	struct Header
	{
		std::string name;
		std::string value;
	};

	std::string			protocol;
	Status				status;
	std::vector<Header> headers;
	std::vector<char>	body;
};
} // namespace http

#endif // HTTPRESPONSE_HPP