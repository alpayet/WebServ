/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Protocol.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 15:40:53 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/core/Protocol.hpp"
#include "application/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/server/application_protocol/cgi/Exception.hpp"
#include "infrastructure/server/application_protocol/cgi/Parser.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/IErrorPagesProvider.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/ReturnException.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/error_lookup.hpp"
#include "infrastructure/server/application_protocol/http/mappers/CgiResponse.hpp"
#include "infrastructure/server/application_protocol/http/request/Parser.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include "infrastructure/server/application_protocol/http/response/Sender.hpp"
#include "infrastructure/server/application_protocol/http/router/Router.hpp"
#include "infrastructure/server/application_protocol/http/update_keep_alive_status.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"

namespace webserv {
namespace http {

Protocol::Protocol(
	request::Parser			  &requestParser,
	cgi::Parser				  &cgiParser,
	Router					  &router,
	response::Sender		  &sender,
	IErrorPagesProvider const &errorPagesProvider
)
	: _requestParser(requestParser), _cgiParser(cgiParser), _router(router), _sender(sender),
	  _errorPagesProvider(errorPagesProvider)
{}

Protocol::PushStatus::Type Protocol::pushRequest(
	Context &context, char const *inputBuf, std::size_t size, RequestStatus::Type status
)
{
	try
	{
		if (status == RequestStatus::TIMEOUT)
			throw Exception(Exception::TIMEOUT);

		Context::Input &context_input = context.input;

		if (inputBuf)
			context_input.buf.insert(context_input.buf.end(), inputBuf, inputBuf + size);

		if (_requestParser.parse(context_input.buf, context_input.state) ==
			request::Parser::COMPLETE)
		{
			update_keep_alive_status(context);
			_router.route(context);

			if (context.stream.stream_info.fd >= 0)
				return (PushStatus::STREAM_AVAILABLE);
			return (PushStatus::COMPLETE);
		}
		return (PushStatus::NEED_MORE_DATA);
	}
	catch (http::ReturnException const &e)
	{
		Context::Output &context_output = context.output;

		prepareDirectResponse(e.getStatusCode(), context_output.response, &context_output.reader);

		return (PushStatus::COMPLETE);
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

		return (PushStatus::COMPLETE);
	}
}

Protocol::PushStatus::Type Protocol::pushStream(
	Context &context, char const *streamBuf, std::size_t size, StreamStatus::Type status
)
{
	try
	{

		if (status == StreamStatus::ERROR)
			throw cgi::Exception(cgi::Exception::READ_FAILED);
		if (status == StreamStatus::TIMEOUT)
			throw cgi::Exception(cgi::Exception::TIMEOUT);

		Context::Stream &context_stream = context.stream;

		context_stream.buf.insert(context_stream.buf.end(), streamBuf, streamBuf + size);

		if (_cgiParser.parse(
				context_stream.buf, status == StreamStatus::END_OF_STREAM, context_stream.state
			) == cgi::Parser::COMPLETE)
		{
			dispatchCgiResponse(context);
			return (PushStatus::COMPLETE);
		}
		return (PushStatus::NEED_MORE_DATA);
	}
	catch (http::ReturnException const &e)
	{
		Context::Output &context_output = context.output;

		prepareDirectResponse(e.getStatusCode(), context_output.response, &context_output.reader);

		return (PushStatus::COMPLETE);
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

		context.shouldKeepAlive = false;
		prepareDirectResponse(500, context_output.response, &context_output.reader);

		return (PushStatus::COMPLETE);
	}
}

Protocol::PullStatus::Type Protocol::pullResponse(Context &context, std::vector<char> &outputBuf)
{
	try
	{
		Context::Output &context_output = context.output;

		if (_sender.produce(
				outputBuf, context_output.response, context_output.reader, context.shouldKeepAlive,
				context_output.state
			) == response::Sender::COMPLETE)
		{
			return (PullStatus::COMPLETE);
		}
		return (PullStatus::HAS_MORE);
	}
	catch (...)
	{
		context.shouldKeepAlive = false;
		return (PullStatus::ERROR);
	}
}

void Protocol::dispatchCgiResponse(Context &context)
{
	Context::Input	&context_input = context.input;
	Context::Stream &context_stream = context.stream;
	Context::Output &context_output = context.output;

	switch (context_stream.state.response.getType())
	{
		case cgi::Response::LOCAL_REDIR:
			if (++context_stream.localRedirDepth > Context::Stream::MAX_LOCAL_REDIR_DEPTH)
				throw Exception(Exception::MAX_LOCAL_REDIR_DEPTH_EXCEEDED);

			context_input.state.request.setTarget(context_stream.state.response.getLocationUri());
			context_input.state.request.setQuery(context_stream.state.response.getLocationQuery());

			context_stream.reset();
			context_output.reset();

			_router.route(context);
			break;
		case cgi::Response::CLIENT_REDIR:
			context_output.response =
				mapper::CgiResponse::toHttpResponse(context_stream.state.response);
			break;
		case cgi::Response::DOCUMENT:
		case cgi::Response::CLIENT_REDIR_DOC:
			context_output.response =
				mapper::CgiResponse::toHttpResponse(context_stream.state.response);

			delete (context.output.reader);
			context_output.reader =
				new fileSystem::Reader(context_stream.state.response.getBodyFd());
			break;

		default:
			break;
	}
}

void Protocol::prepareDirectResponse(
	unsigned short statusCode, Response &response, app::IResourceReader **reader
)
{
	std::map<int, std::string> const &error_pages = _errorPagesProvider.getErrPages();

	std::map<int, std::string>::const_iterator it = error_pages.find(statusCode);
	if (it != error_pages.end())
	{
		app::SystemResourceInfo const &error_page_info =
			_errorPagesProvider.locateErrorPage(it->second);

		if (error_page_info.exists && !(error_page_info.type == domain::COLLECTION) &&
			(error_page_info.permissions & domain::READABLE))
		{
			delete *reader;
			*reader = new fileSystem::Reader(error_page_info.resourcePath);
			response = Response::buildErrorPage(statusCode, error_page_info);
			return;
		}
	}
	response = Response::buildDefault(statusCode);
}

Protocol::PushStatus::Type Protocol::handleError(Context &context, cgi::Exception const &e)
{
	Context::Output &context_output = context.output;
	unsigned short	 statusCode = to_status_code(e.getErrorCode());

	prepareDirectResponse(statusCode, context_output.response, &context_output.reader);

	return (PushStatus::COMPLETE);
}
} // namespace http
} // namespace webserv
