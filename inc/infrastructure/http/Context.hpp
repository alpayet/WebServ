/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 04:34:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCONTEXT_HPP
#define HTTPCONTEXT_HPP

#include "infrastructure/http/request/ParsingState.hpp"
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
		request::ParsingState state;
		std::vector<char>	  inputBuf;
	};
	struct Output
	{

		Output(void) : reader(NULL) {}
		~Output(void) { delete reader; }

		response::Sender::State state;
		std::vector<char>		rawHeaderBlock;
		std::vector<char>		rawbody;
		app::IResourceReader   *reader;
	};

	Input  input;
	Output output;
};
} // namespace http

#endif // HTTPCONTEXT_HPP