/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 00:04:33 by alpayet          ###   ########.fr       */
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
void Handler::createContext(unsigned int id) { _contexts.insert(std::make_pair(id, Context())); }

void Handler::push(unsigned int id, std::vector<char> const &inputBuf)
{
	if (_contexts.find(id) == _contexts.end())
		throw std::out_of_range("HttpContext not found for this id");

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
	if (_contexts.find(id) == _contexts.end())
		throw std::out_of_range("HttpContext not found for this id");

	Context::Output &context_output = _contexts[id].output;

	if (_sender.produce(_contexts[id].output) == response::Sender::complete)
		context_output.isResponseComplete = true;

	return (context_output.buf);
}

bool Handler::isRequestComplete(unsigned int id)
{
	if (_contexts.find(id) == _contexts.end())
		throw std::out_of_range("HttpContext not found for this id");

	return (_contexts[id].input.isRequestComplete);
}

bool Handler::isResponseComplete(unsigned int id)
{
	if (_contexts.find(id) == _contexts.end())
		throw std::out_of_range("HttpContext not found for this id");

	return (_contexts[id].output.isResponseComplete);
}

} // namespace http
