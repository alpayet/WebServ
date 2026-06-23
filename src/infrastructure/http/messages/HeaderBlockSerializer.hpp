/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:16:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/22 21:30:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/messages/HeaderBlockSerializer.hpp"
#include "infrastructure/http/messages/Response.hpp"
#include <iterator>
#include <sstream>

namespace http {
std::vector<char> HeaderBlockSerializer::serialize(Response const &response)
{
	std::string headerBlock;

	headerBlock += response.protocol;
	headerBlock += SP;

	std::stringstream ss;
	ss << response.status.statusCode;
	headerBlock += ss.str();
	headerBlock += SP;

	headerBlock += response.status.reason;
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
} // namespace http
