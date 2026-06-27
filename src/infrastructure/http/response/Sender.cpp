/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:31:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 06:30:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Sender.hpp"
#include "infrastructure/http/IHttpVersionProvider.hpp"
#include "infrastructure/http/response/HeaderBlockSerializer.hpp"

namespace http {
namespace response {

Sender::Sender(IHttpVersionProvider &httpVersionProvider)
	: _httpVersionProvider(httpVersionProvider)
{}

Sender::State Sender::produce(
	std::vector<char>	 &outputBuf,
	Response const		 &response,
	app::IResourceReader *reader,
	State				  state
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
			state = complete;
			break;
		case resource:
			outputBuf.clear();
			state = complete;
			break;
		default:
			break;
	}
	return (state);
}

} // namespace response
} // namespace http
