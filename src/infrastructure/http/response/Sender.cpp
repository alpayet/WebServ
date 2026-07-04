/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:31:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 04:32:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Sender.hpp"
#include "application/ports/IResourceReader.hpp"
#include "infrastructure/http/IHttpVersionProvider.hpp"
#include "infrastructure/http/response/HeaderBlockSerializer.hpp"
#include "infrastructure/http/response/Response.hpp"

namespace http {
namespace response {

Sender::State::State(void) : step(HeaderBlock), totalBytesRead(0), cgiBuf() {}

Sender::Sender(IHttpVersionProvider &httpVersionProvider)
	: _httpVersionProvider(httpVersionProvider)
{}

void Sender::State::reset(void)
{
	step = HeaderBlock;
	totalBytesRead = 0;
	cgiBuf.clear();
}

Sender::Step Sender::produce(
	std::vector<char>	 &outputBuf,
	Response const		 &response,
	app::IResourceReader *reader,
	State				 &state
)
{
	switch (state.step)
	{
		case HeaderBlock:
			outputBuf.clear();
			HeaderBlockSerializer::serialize(
				outputBuf, response, _httpVersionProvider.getHttpVersion()
			);
			state.step = (reader) ? resource : body;
			break;
		case body:
			outputBuf.clear();
			outputBuf = response.body;
			state.step = complete;
			break;
		case resource:
		{
			outputBuf.clear();
			size_t const bytes_read =
				reader->read(outputBuf, response.contentLength - state.totalBytesRead);

			if (bytes_read == 0 && state.totalBytesRead < response.contentLength)
			{
				// TODO: a vori avec luca si il catch les throw et deconnecte le client
				// throw ;
			}
			if (state.totalBytesRead + bytes_read == response.contentLength)
				state.step = complete;

			state.totalBytesRead += bytes_read;
			break;
		}
		case cgi:
		default:
			break;
	}
	return (state.step);
}

} // namespace response
} // namespace http
