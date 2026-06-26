/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:54:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 23:14:13 by alpayet          ###   ########.fr       */
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

	virtual void createContext(unsigned int id);

	virtual void push(unsigned int id, std::vector<char> const &inputBuf);

	virtual std::vector<char> const &pull(unsigned int id);

	virtual bool isRequestComplete(unsigned int id);
	virtual bool isResponseComplete(unsigned int id);

  private:
	Handler(Handler const &src);
	Handler &operator=(Handler const &rhs);

	std::map<int, Context> _contexts;

	request::Parser	 &_parser;
	Router			 &_router;
	response::Sender &_sender;
};
} // namespace http

#endif // HTTPHANDLER_HPP