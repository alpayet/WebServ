/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:31:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:19:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/response/Sender.hpp"
#include "application/ports/IResourceReader.hpp"
#include "infrastructure/server/application_protocol/http/IHttpVersionProvider.hpp"
#include "infrastructure/server/application_protocol/http/response/HeaderBlockSerializer.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include <stdexcept>

namespace webserv {
namespace http {
namespace response {

Sender::State::State(void) : step(HEADER_BLOCK), totalBytesRead(0), cgiBuf() {}

void Sender::State::reset(void)
{
	step = HEADER_BLOCK;
	totalBytesRead = 0;
	cgiBuf.clear();
}

Sender::Sender(IHttpVersionProvider const &httpVersionProvider)
	: _httpVersionProvider(httpVersionProvider)
{}

Sender::Step Sender::produce(
	std::vector<char>	 &outputBuf,
	Response			 &response,
	app::IResourceReader *reader,
	bool				  shouldKeepAlive,
	State				 &state
)
{
	switch (state.step)
	{
		case HEADER_BLOCK:
			outputBuf.clear();

			response.setHeaderConnection(shouldKeepAlive);
			HeaderBlockSerializer::serialize(
				outputBuf, response, _httpVersionProvider.getHttpVersion()
			);

			if (reader)
				state.step = RESOURCE;
			else if (response.hasBody())
				state.step = BODY;
			else
				state.step = COMPLETE;
			break;
		case BODY:
			outputBuf.clear();
			outputBuf = response.getBody();

			state.step = COMPLETE;
			break;
		case RESOURCE:
		{
			outputBuf.clear();

			size_t const bytes_read =
				reader->read(outputBuf, response.getContentLength() - state.totalBytesRead);

			if (bytes_read == 0 && state.totalBytesRead < response.getContentLength())
				throw std::runtime_error("Resource truncated unexpectedly");

			state.totalBytesRead += bytes_read;
			if (state.totalBytesRead == response.getContentLength())
				state.step = COMPLETE;
			break;
		}
		default:
			break;
	}
	return (state.step);
}

} // namespace response
} // namespace http
}