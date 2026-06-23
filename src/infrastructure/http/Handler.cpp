/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 04:07:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Handler.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/router/Router.hpp"

namespace http {

Handler::Handler(Parser &requestParser, Router &router)
	: _requestParser(requestParser), _router(router)
{}

// TODO : check pour linsertion
void Handler::createContext(unsigned int id) { _contexts.insert(std::make_pair(id, Context())); }

bool Handler::push(unsigned int id, std::vector<char> &buf)
{
	if (_contexts.find(id) == _contexts.end())
		throw std::out_of_range("HttpContext not found for this id");

	Context &context = _contexts[id];

	context.inputBuf.insert(context.inputBuf.end(), buf.begin(), buf.end());

	if (_requestParser.parse(context.inputBuf, context.state) == ParsingState::complete)
	{
		_router.route(context);
		return (false);
	}
	return (true);
}
bool Handler::pull(unsigned int id, std::vector<char> &buf)
{
	if (_contexts.find(id) == _contexts.end())
		throw std::out_of_range("HttpContext not found for this id");

	Context &context = _contexts[id];
}

} // namespace http
