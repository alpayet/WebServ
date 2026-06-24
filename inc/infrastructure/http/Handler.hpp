/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:54:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/24 04:48:57 by alpayet          ###   ########.fr       */
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
	Handler(request::Parser &parser, Router &router);

	virtual void createContext(unsigned int id);

	virtual void			  push(unsigned int id, std::vector<char> &inputBuf);
	virtual std::vector<char> pull(unsigned int id);

	virtual bool isRequestComplete(unsigned int id);
	virtual bool isResponseComplete(unsigned int id);

  private:
	Handler(Handler const &src);
	Handler &operator=(Handler const &rhs);

	request::Parser		  &_parser;
	Router				  &_router;
	std::map<int, Context> _contexts;
};
} // namespace http

#endif // HTTPHANDLER_HPP