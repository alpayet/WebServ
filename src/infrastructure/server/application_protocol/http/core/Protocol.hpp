/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Protocol.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:54:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/05 02:39:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPROTOCOL_HPP
#define HTTPPROTOCOL_HPP

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"

namespace http {

class Router;
class IErrorPagesProvider;
class IErrorPageLocator;
class Context;

class Protocol
{
  public:
	typedef webserv::appProtocol::IProtocol IProtocol;
	typedef IProtocol::PushStatus			PushStatus;
	typedef IProtocol::PullStatus			PullStatus;
	typedef IProtocol::RequestStatus		RequestStatus;
	typedef IProtocol::StreamStatus			StreamStatus;

	Protocol(
		request::Parser			  &requestParser,
		cgi::Parser				  &cgiParser,
		Router					  &router,
		response::Sender		  &sender,
		IErrorPagesProvider const &errorPagesProvider
	);

	PushStatus
	pushRequest(Context &context, std::vector<char> const &inputBuf, RequestStatus::Type status);
	PushStatus
	pushStream(Context &context, std::vector<char> const &streamBuf, StreamStatus::Type status);

	PullStatus pullResponse(Context &context, std::vector<char> &outputBuf);

  private:
	Protocol(Protocol const &src);
	Protocol &operator=(Protocol const &rhs);

	request::Parser			  &_requestParser;
	cgi::Parser				  &_cgiParser;
	Router					  &_router;
	response::Sender		  &_sender;
	IErrorPagesProvider const &_errorPagesProvider;

	void dispatchCgiResponse(Context &context);

	void prepareDirectResponse(
		unsigned short statusCode, Response &response, app::IResourceReader **reader
	);

	template <typename ExceptionType>
	PushStatus handleError(Context &context, ExceptionType const &e);
};
} // namespace http

#include "Protocol.tpp"

#endif // HTTPPROTOCOL_HPP
