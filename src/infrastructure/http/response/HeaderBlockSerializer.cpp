/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:16:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 23:44:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/HeaderBlockSerializer.hpp"
#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/StatusReason.hpp"
#include "infrastructure/http/response/Response.hpp"
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
	ss << response.statusCode;
	headerBlock += ss.str();
	headerBlock += SP;

	headerBlock += getReasonPhrase(response.statusCode);
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

	outputBuf.insert(outputBuf.end(), headerBlock.begin(), headerBlock.end());
}
} // namespace response
} // namespace http
