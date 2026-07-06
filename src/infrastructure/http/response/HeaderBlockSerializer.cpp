/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:16:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 00:49:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/HeaderBlockSerializer.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/response/Response.hpp"
#include "infrastructure/http/response/statusReason.hpp"
#include <iterator>
#include <sstream>

namespace http {
namespace response {
void HeaderBlockSerializer::serialize(
	std::vector<char> &outputBuf, Response const &response, std::string const &httpVersion
)
{
	std::string headerBlock;

	headerBlock += httpVersion;
	headerBlock += SP;

	std::stringstream ss;
	ss << response.statusLine.statusCode;
	headerBlock += ss.str();
	headerBlock += SP;

	headerBlock += response.statusLine.reason;
	headerBlock += CRLF;

	for (std::vector<Response::Header>::const_iterator i = response.headers.begin();
		 i != response.headers.end(); ++i)
	{
		headerBlock += i->key;
		headerBlock += COLON;
		headerBlock += SP;
		headerBlock += i->value;
		headerBlock += CRLF;
	}
	headerBlock += CRLF;

	outputBuf.insert(outputBuf.end(), headerBlock.begin(), headerBlock.end());
}
} // namespace response
} // namespace http
