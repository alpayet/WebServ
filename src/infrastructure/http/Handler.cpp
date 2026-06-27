/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 07:42:23 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Handler.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include "infrastructure/http/router/Router.hpp"

namespace http {
Handler::Handler(request::Parser &parser, Router &router, response::Sender &sender)
	: _parser(parser), _router(router), _sender(sender)
{}

// TODO : check pour linsertion

void Handler::prepareContext(unsigned int id) { _contexts[id].reset(); }

void Handler::push(unsigned int id, std::vector<char> const &inputBuf)
{

	Context::Input &context_input = _contexts[id].input;

	context_input.buf.insert(context_input.buf.end(), inputBuf.begin(), inputBuf.end());

	if (_parser.parse(context_input.buf, context_input.state) == request::Parser::complete)
	{
		_router.route(_contexts[id]);
		context_input.isRequestComplete = true;
	}
}

std::vector<char> const &Handler::pull(unsigned int id)
{
	Context::Output &context_output = _contexts[id].output;

	if (_sender.produce(
			context_output.buf, context_output.response, context_output.reader, context_output.state
		) == response::Sender::complete)
		context_output.isResponseComplete = true;

	return (context_output.buf);
}

bool Handler::isRequestComplete(unsigned int id) { return (_contexts[id].input.isRequestComplete); }

bool Handler::isResponseComplete(unsigned int id)
{
	return (_contexts[id].output.isResponseComplete);
}

} // namespace http
