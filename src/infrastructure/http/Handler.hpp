/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:54:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:20:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLER_HPP
#define HTTPHANDLER_HPP

#include "infrastructure/ITransfertHandler.hpp"
#include "infrastructure/http/Context.hpp"

namespace http {

class Router;
class IErrorPagesProvider;
class IErrorPageLocator;

class Handler
{
  public:
	Handler(
		request::Parser		&requestParser,
		cgi::Parser			&cgiParser,
		Router				&router,
		response::Sender	&sender,
		const IErrorPagesProvider &errorPagesProvider
	);

	void prepareContext(Context &context);

	ITransfertHandler::ProcessingStatus
	pushRequest(Context &context, std::vector<char> const &inputBuf, ITransfertHandler::RequestStatus::Type status);
	ITransfertHandler::ProcessingStatus
	pushStream(Context &context, std::vector<char> const &streamBuf, ITransfertHandler::StreamStatus::Type status);

	ITransfertHandler::ProcessingStatus pull(Context &context, std::vector<char>& outputBuf);

	void reset(Context &context);

  private:
	Handler(Handler const &src);
	Handler &operator=(Handler const &rhs);

	request::Parser		&_requestParser;
	cgi::Parser			&_cgiParser;
	Router				&_router;
	response::Sender	&_sender;
	const IErrorPagesProvider &_errorPagesProvider;

	void dispatchCgiResponse(Context &context);

	void prepareDirectResponse(
		unsigned short statusCode, Response &response, app::IResourceReader **reader
	);

	template <typename ExceptionType>
	ITransfertHandler::ProcessingStatus handleError(Context &context, ExceptionType const &e);
};
} // namespace http

#include "Handler.tpp"

#endif // HTTPHANDLER_HPP
