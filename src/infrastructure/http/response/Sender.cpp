/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:31:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 21:41:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Sender.hpp"
#include "application/ports/IResourceReader.hpp"
#include "infrastructure/http/IHttpVersionProvider.hpp"
#include "infrastructure/http/response/HeaderBlockSerializer.hpp"
#include "infrastructure/http/response/Response.hpp"

namespace http {
namespace response {

Sender::Sender(IHttpVersionProvider &httpVersionProvider)
	: _httpVersionProvider(httpVersionProvider)
{}

Sender::State Sender::produce(
	std::vector<char>	 &outputBuf,
	Response const		 &response,
	app::IResourceReader *reader,
	State				 &state
)
{
	switch (state)
	{
		case HeaderBlock:
			outputBuf.clear();
			HeaderBlockSerializer::serialize(
				outputBuf, response, _httpVersionProvider.getHttpVersion()
			);
			state = (reader) ? resource : body;
			break;
		case body:
			outputBuf.clear();
			outputBuf = response.body;
			state = complete;
			break;
		case resource:
			outputBuf.clear();
			if (reader->readChunk(outputBuf) == 0)
				state = complete;
			break;
		default:
			break;
	}
	return (state);
}

} // namespace response
} // namespace http
