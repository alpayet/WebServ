/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:31:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 23:49:48 by alpayet          ###   ########.fr       */
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

Sender::State Sender::produce(Context::Output &context)
{
	switch (context.state)
	{
		case HeaderBlock:
			context.buf.clear();
			HeaderBlockSerializer::serialize(
				context.buf, context.response, _httpVersionProvider.getHttpVersion()
			);

			context.state = (context.reader) ? resource : body;
			break;
		case body:
			context.buf.clear();
			/* code */
		case resource:
			context.buf.clear();
		default:
			break;
	}
}

} // namespace response
} // namespace http
