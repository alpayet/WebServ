/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:31:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/03 16:36:30 by ludebion         ###   ########.fr       */
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

void Sender::State::reset(void)
{
	step = HeaderBlock;
	totalBytesRead = 0;
	cgiBuf.clear();
}

Sender::Sender(const IHttpVersionProvider &httpVersionProvider)
	: _httpVersionProvider(httpVersionProvider)
{}

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
			if (reader)
				state.step = resource;
			else if (response.hasBody())
				state.step = body;
			else
				state.step = complete;
			break;
		case body:
			outputBuf.clear();
			outputBuf = response.getBody();
			state.step = complete;
			break;
		case resource:
		{
			outputBuf.clear();
			size_t const bytes_read =
				reader->read(outputBuf, response.getContentLength() - state.totalBytesRead);

			if (bytes_read == 0 && state.totalBytesRead < response.getContentLength())
			{
				// TODO: a vori avec luca si il catch les throw et deconnecte le client
				// throw "caca";
			}

			state.totalBytesRead += bytes_read;
			if (state.totalBytesRead == response.getContentLength())
				state.step = complete;
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
