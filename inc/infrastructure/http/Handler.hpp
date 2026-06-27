/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:54:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 06:27:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLER_HPP
#define HTTPHANDLER_HPP

#include "infrastructure/ITransfertHandler.hpp"
#include "infrastructure/http/Context.hpp"

namespace http {

namespace request {
class Parser;
} // namespace request

class Router;

class Handler : public ITransfertHandler
{
  public:
	Handler(request::Parser &parser, Router &router, response::Sender &sender);

	virtual void prepareContext(unsigned int id);

	virtual void push(unsigned int id, std::vector<char> const &inputBuf);

	virtual std::vector<char> const &pull(unsigned int id);

	virtual bool isRequestComplete(unsigned int id);
	virtual bool isResponseComplete(unsigned int id);

  private:
	Handler(Handler const &src);
	Handler &operator=(Handler const &rhs);

// TODO : a voir pour mettre cette limite de max de connections dans la config ou pas
	Context _contexts[1024];

	request::Parser	 &_parser;
	Router			 &_router;
	response::Sender &_sender;
};
} // namespace http

#endif // HTTPHANDLER_HPP