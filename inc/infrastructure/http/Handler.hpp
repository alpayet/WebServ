/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:54:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 04:07:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLER_HPP
#define HTTPHANDLER_HPP

#include "infrastructure/ITransfertHandler.hpp"
#include "infrastructure/http/Context.hpp"

namespace http {
class Parser;
class Router;

class Handler : public ITransfertHandler
{
  public:
	Handler(Parser &requestParser, Router &router);

	virtual void createContext(unsigned int id);

	virtual bool push(unsigned int id, std::vector<char> &inputBuf);
	virtual bool pull(unsigned int id, std::vector<char> &outputBuf);

  private:
	Handler(Handler const &src);
	Handler &operator=(Handler const &rhs);

	Parser				  &_requestParser;
	Router				  &_router;
	std::map<int, Context> _contexts;
};
} // namespace http

#endif // HTTPHANDLER_HPP