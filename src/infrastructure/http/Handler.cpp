/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:50:24 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Handler.hpp"
#include "application/Exception.hpp"
#include "cgi/Exception.hpp"
#include "cgi/Parser.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/exceptions/IErrorPagesProvider.hpp"
#include "infrastructure/http/exceptions/ReturnException.hpp"
#include "infrastructure/http/exceptions/error_lookup.hpp"
#include "infrastructure/http/mappers/CgiResponseMapper.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Response.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"
#include "infrastructure/http/updateKeepAliveStatus.hpp"

namespace http {
Handler::Handler(
	request::Parser		&parser,
	cgi::Parser			&cgiParser,
	Router				&router,
	response::Sender	&sender,
	const IErrorPagesProvider &errorPagesProvider
)
	: _requestParser(parser), _cgiParser(cgiParser), _router(router), _sender(sender),
	  _errorPagesProvider(errorPagesProvider)
{}

// TODO : check pour linsertion

void Handler::prepareContext(Context &context) { context.reset(); }

ITransfertHandler::ProcessingStatus
Handler::pushRequest(Context &context, std::vector<char> const &inputBuf, ITransfertHandler::RequestStatus::Type status)
{
	try
	{
		if (status == ITransfertHandler::RequestStatus::timeOut)
			throw Exception(Exception::timeOut);

		Context::Input &context_input = context.input;

		context_input.buf.insert(context_input.buf.end(), inputBuf.begin(), inputBuf.end());

		if (_requestParser.parse(context_input.buf, context_input.state) ==
			request::Parser::complete)
		{
			updateKeepAliveStatus(context);
			_router.route(context);
			return (ITransfertHandler::complete);
		}
		return (ITransfertHandler::needMoreData);
	}
	catch (http::ReturnException const &e)
	{
		Context::Output &context_output = context.output;

		prepareDirectResponse(e.getStatusCode(), context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
	}
	catch (http::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (fileSystem::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (app::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (domain::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (...)
	{
		Context::Output &context_output = context.output;

		prepareDirectResponse(500, context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
	}
}

ITransfertHandler::ProcessingStatus
Handler::pushStream(Context &context, std::vector<char> const &streamBuf, ITransfertHandler::StreamStatus::Type status)
{
	try
	{
		if (status == ITransfertHandler::StreamStatus::timeOut)
			throw cgi::Exception(cgi::Exception::timeOut);

		Context::Stream &context_stream = context.stream;

		context_stream.buf.insert(context_stream.buf.end(), streamBuf.begin(), streamBuf.end());

		if (_cgiParser.parse(context_stream.buf, status, context_stream.state) ==
			cgi::Parser::complete)
		{
			dispatchCgiResponse(context);
			return (ITransfertHandler::complete);
		}
		return (ITransfertHandler::needMoreData);
	}
	catch (http::ReturnException const &e)
	{
		Context::Output &context_output = context.output;

		prepareDirectResponse(e.getStatusCode(), context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
	}
	catch (http::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (fileSystem::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (cgi::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (app::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (domain::Exception const &e)
	{
		return (handleError(context, e));
	}
	catch (...)
	{
		Context::Output &context_output = context.output;

		prepareDirectResponse(500, context_output.response, &context_output.reader);

		return (ITransfertHandler::complete);
	}
}

ITransfertHandler::ProcessingStatus Handler::pull(Context &context, std::vector<char>& outputBuf)
{
	// TODO A voir avec luca si il catch des exection pour close la connection dun client
	Context::Output &context_output = context.output;

	if (_sender.produce(
			outputBuf, context_output.response, context_output.reader, context_output.state
		) == response::Sender::complete)
		return (ITransfertHandler::complete);
	// TODO: ne pas oubleir de reset le contexte ici / a voir avec luca si il reset

	return (ITransfertHandler::needMoreData);
}

void Handler::reset(Context &context) { context.reset(); }

void Handler::dispatchCgiResponse(Context &context)
{
	Context::Input	&context_input = context.input;
	Context::Stream &context_stream = context.stream;
	Context::Output &context_output = context.output;

	switch (context_stream.state.response.getType())
	{
		case cgi::Response::localRedir:
			if (++context_stream.localRedirDepth > Context::Stream::MAX_LOCAL_REDIR_DEPTH)
				throw Exception(Exception::maxLocalRedirDepthExceeded);

			context_input.state.request.setTarget(context_stream.state.response.getLocationUri());
			context_input.state.request.setQuery(context_stream.state.response.getLocationQuery());

			context_stream.reset();
			context_output.reset();

			_router.route(context);
			break;
		case cgi::Response::clientRedir:
			context_output.response =
				CgiResponseMapper::toHttpResponse(context_stream.state.response);
			break;

		case cgi::Response::document:
		case cgi::Response::clientRedirDoc:
			context_output.response =
				CgiResponseMapper::toHttpResponse(context_stream.state.response);

			delete (context.output.reader);
			context_output.reader =
				new fileSystem::Reader(context_stream.state.response.getBodyFd());
			break;

		default:
			break;
	}
}

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
