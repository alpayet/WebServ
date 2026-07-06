/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 06:21:50 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Handler.hpp"
#include "application/Exception.hpp"
#include "cgi/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/exceptions/IErrorPagesProvider.hpp"
#include "infrastructure/http/exceptions/ReturnException.hpp"
#include "infrastructure/http/exceptions/error_lookup.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Response.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"

namespace http {
Handler::Handler(
	request::Parser		&parser,
	Router				&router,
	response::Sender	&sender,
	IErrorPagesProvider &errorPagesProvider
)
	: _parser(parser), _router(router), _sender(sender), _errorPagesProvider(errorPagesProvider)
{}

// TODO : check pour linsertion

void Handler::prepareContext(unsigned int id) { _contexts[id].reset(); }

ITransfertHandler::ProcessingStatus
Handler::pushRequest(unsigned int id, std::vector<char> const &inputBuf, RequestStatus status)
{
	try
	{
		if (status == timeOut)
			throw Exception(Exception::timeOut);

		Context::Input &context_input = _contexts[id].input;

		context_input.buf.insert(context_input.buf.end(), inputBuf.begin(), inputBuf.end());

		if (_parser.parse(context_input.buf, context_input.state) == request::Parser::complete)
		{
			_router.route(_contexts[id]);
			return (ITransfertHandler::complete);
		}
		return (ITransfertHandler::needMoreData);
	}
	catch (http::ReturnException const &e)
	{
		Context::Output &context_output = _contexts[id].output;

		prepareDirectResponse(e.getStatusCode(), context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
	}
	catch (http::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (fileSystem::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (app::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (domain::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (...)
	{
		Context::Output &context_output = _contexts[id].output;

		prepareDirectResponse(500, context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
	}
}

ITransfertHandler::ProcessingStatus
Handler::pushStream(unsigned int id, std::vector<char> const &streamBuf, StreamStatus status)
{
	try
	{
		if (status == timeOut)
			throw cgi::Exception(cgi::Exception::timeOut);

		Context::Stream &context_stream = _contexts[id].stream;

		context_stream.buf.insert(context_stream.buf.end(), streamBuf.begin(), streamBuf.end());

		if (cgi::Parser::parse(context_stream.buf, context_stream.state) == cgi::Parser::complete)
		{
			// TODO a fini
			if (context_stream.state.response.type == cgi::Response::localRedir)
			{
				if (++context_stream.localRedirDepth > Context::Stream::MAX_LOCAL_REDIR_DEPTH)
					throw Exception(Exception::maxLocalRedirDepthExceeded);

				context_stream.reset();
				_contexts[id].output.reset();
				_contexts[id].input.state.request.startLine.target =
					context_stream.state.response.location;
				_router.route(_contexts[id]);
			}
			return (ITransfertHandler::complete);
		}
		return (ITransfertHandler::needMoreData);
	}
	catch (http::ReturnException const &e)
	{
		Context::Output &context_output = _contexts[id].output;

		prepareDirectResponse(e.getStatusCode(), context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
	}
	catch (http::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (fileSystem::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (cgi::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (app::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (domain::Exception const &e)
	{
		return (handleError(id, e));
	}
	catch (...)
	{
		Context::Output &context_output = _contexts[id].output;

		prepareDirectResponse(500, context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
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
	// TODO: ne pas oubleir de reset le contexte ici / a voir avec luca si il reset

	return (context_output.buf);
}

bool Handler::isResponseComplete(unsigned int id)
{
	return (_contexts[id].output.isResponseComplete);
}

void Handler::reset(unsigned int id) { _contexts[id].reset(); }

void Handler::prepareDirectResponse(
	unsigned short statusCode, Response &response, app::IResourceReader **reader
)
{
	std::map<int, std::string> const &error_pages = _errorPagesProvider.getErrPages();

	std::map<int, std::string>::const_iterator it = error_pages.find(statusCode);
	if (it != error_pages.end())
	{
		app::SystemResourceInfo const &error_page_info =
			_errorPagesProvider.locateErrorPage(it->second);

		if (error_page_info.exists && !(error_page_info.type == domain::collection) &&
			(error_page_info.permissions & domain::readable))
		{
			delete *reader;
			*reader = new fileSystem::Reader(error_page_info.resourcePath);
			response = Response::buildErrorPage(statusCode, error_page_info);
			return;
		}
	}
	response = Response::buildDefault(statusCode);
}

} // namespace http
