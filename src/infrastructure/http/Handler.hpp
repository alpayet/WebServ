/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:54:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 22:38:34 by alpayet          ###   ########.fr       */
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

class Handler : public ITransfertHandler
{
  public:
	Handler(
		request::Parser		&requestParser,
		cgi::Parser			&cgiParser,
		Router				&router,
		response::Sender	&sender,
		IErrorPagesProvider &errorPagesProvider
	);

	virtual void prepareContext(unsigned int id);

	virtual ProcessingStatus
	pushRequest(unsigned int id, std::vector<char> const &inputBuf, RequestStatus::Type status);
	virtual ProcessingStatus
	pushStream(unsigned int id, std::vector<char> const &streamBuf, StreamStatus::Type status);

	virtual std::vector<char> const &pull(unsigned int id);

	virtual bool isResponseComplete(unsigned int id);

	virtual void reset(unsigned int id);

  private:
	Handler(Handler const &src);
	Handler &operator=(Handler const &rhs);

	// TODO : a voir pour mettre cette limite de max de connections dans la config ou pas
	Context _contexts[1024];

	request::Parser		&_requestParser;
	cgi::Parser			&_cgiParser;
	Router				&_router;
	response::Sender	&_sender;
	IErrorPagesProvider &_errorPagesProvider;

	void dispatchCgiResponse(Context &context);

	void prepareDirectResponse(
		unsigned short statusCode, Response &response, app::IResourceReader **reader
	);

	template <typename ExceptionType>
	ITransfertHandler::ProcessingStatus handleError(int id, ExceptionType const &e);
};
} // namespace http

#include "Handler.tpp"

#endif // HTTPHANDLER_HPP