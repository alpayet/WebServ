/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:31:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 19:53:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Sender.hpp"

namespace http {
namespace response {

Sender::Sender(http::IVersionProvider &versionProvider) : _versionProvider(versionProvider) {}

Sender::State Sender::produce(std::vector<char> &outputBuf, Context::Output &context)
{
	switch (context.state)
	{
		case HeaderBlock:

		case body:
			/* code */
		case resource:
			/* code */
			break;

		default:
			break;
	}
}

} // namespace response
} // namespace http
