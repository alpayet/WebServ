/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 00:29:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Handler.hpp"
#include "application/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Response.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"

namespace http {
Handler::Handler(request::Parser &parser, Router &router, response::Sender &sender)
	: _parser(parser), _router(router), _sender(sender)
{}

// TODO : check pour linsertion

void Handler::prepareContext(unsigned int id) { _contexts[id].reset(); }

void Handler::push(unsigned int id, std::vector<char> const &inputBuf)
{
	try
	{
		Context::Input &context_input = _contexts[id].input;

		context_input.buf.insert(context_input.buf.end(), inputBuf.begin(), inputBuf.end());

		if (_parser.parse(context_input.buf, context_input.state) == request::Parser::complete)
		{
			_router.route(_contexts[id]);
			context_input.isRequestComplete = true;
		}
	}
	catch (http::Exception const &e)
	{
		Response::Builder builder;

		_contexts[id].output.response = builder.buildError(e.getErrorCode());
		_contexts[id].input.isRequestComplete = true;
	}
	catch (fileSystem::Exception const &e)
	{
		Response::Builder builder;

		_contexts[id].output.response = builder.buildError(e.getErrorCode());
		_contexts[id].input.isRequestComplete = true;
	}
	catch (app::Exception const &e)
	{
		Response::Builder builder;

		_contexts[id].output.response = builder.buildError(e.getErrorCode());
		_contexts[id].input.isRequestComplete = true;
	}
	catch (domain::Exception const &e)
	{
		Response::Builder builder;

		_contexts[id].output.response = builder.buildError(e.getErrorCode());
		_contexts[id].input.isRequestComplete = true;
	}
}

std::vector<char> const &Handler::pull(unsigned int id)
{
	// TODO A voir avec luca si il catch des exection pour close la connection dun client
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
