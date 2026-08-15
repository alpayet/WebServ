/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:16:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:18:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/response/HeaderBlockSerializer.hpp"
#include "infrastructure/server/application_protocol/parsing/constants.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include "infrastructure/server/application_protocol/http/response/get_status_reason.hpp"
#include <iterator>
#include <sstream>

namespace webserv {
namespace http {
namespace response {
void HeaderBlockSerializer::serialize(
	std::vector<char> &outputBuf, Response const &response, std::string const &httpVersion
)
{
	std::string headerBlock;

	headerBlock += httpVersion;
	headerBlock += parse::SP;

	std::stringstream ss;
	ss << response.getStatusCode();
	headerBlock += ss.str();
	headerBlock += parse::SP;

	headerBlock += response.getStatusReason();
	headerBlock += parse::CRLF;

	for (std::vector<Response::Header>::const_iterator i = response.getHeaders().begin();
		 i != response.getHeaders().end(); ++i)
	{
		headerBlock += i->key;
		headerBlock += parse::COLON;
		headerBlock += parse::SP;
		headerBlock += i->value;
		headerBlock += parse::CRLF;
	}
	headerBlock += parse::CRLF;

	outputBuf.insert(outputBuf.end(), headerBlock.begin(), headerBlock.end());
}
} // namespace response
} // namespace http
}
