/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:16:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 19:45:40 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/HeaderBlockSerializer.hpp"
#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/response/Response.hpp"
#include <iterator>
#include <sstream>

namespace http {
namespace response {
std::vector<char> HeaderBlockSerializer::serialize(Response const &response)
{
	std::string headerBlock;

	// TODO: injecter le protocol
	//  headerBlock += response.protocol;
	headerBlock += SP;

	std::stringstream ss;
	ss << response.statusCode;
	headerBlock += ss.str();
	headerBlock += SP;

	// headerBlock += response.status.reason;
	headerBlock += CRLF;

	for (std::vector<Response::Header>::const_iterator i = response.headers.begin();
		 i != response.headers.end(); ++i)
	{
		headerBlock += i->key;
		headerBlock += COLON;
		headerBlock += i->value;
		headerBlock += CRLF;
	}
	headerBlock += CRLF;
	return (std::vector<char>(headerBlock.begin(), headerBlock.end()));
}
} // namespace response
} // namespace http
