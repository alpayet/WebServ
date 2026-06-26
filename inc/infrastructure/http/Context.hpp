/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 01:51:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCONTEXT_HPP
#define HTTPCONTEXT_HPP

#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Response.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include <vector>

namespace app {
class IResourceReader;
} // namespace app

namespace http {
struct Context
{
	struct Input
	{
		Input(void) : isRequestComplete(false) {}

		std::vector<char>	   buf;
		request::Parser::State state;
		bool				   isRequestComplete;
	};
	struct Output
	{
		Output(void) : state(response::Sender::HeaderBlock), reader(NULL), isResponseComplete(false)
		{}
		~Output(void) { delete reader; }

		std::vector<char>		buf;
		response::Sender::State state;
		Response				response;
		app::IResourceReader   *reader;
		bool					isResponseComplete;
	};

	Input  input;
	Output output;
};
} // namespace http

#endif // HTTPCONTEXT_HPP