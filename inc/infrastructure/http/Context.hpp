/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 06:28:44 by alpayet          ###   ########.fr       */
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
class Context
{
  public:
	class Input
	{
	  public:
		Input(void);

		std::vector<char>	   buf;
		request::Parser::State state;
		bool				   isRequestComplete;

		void reset(void);

	  private:
		Input(Input const &src);
		Input &operator=(Input const &rhs);
	};
	class Output
	{
	  public:
		Output(void);
		~Output(void);

		std::vector<char>		buf;
		response::Sender::State state;
		Response				response;
		app::IResourceReader   *reader;
		bool					isResponseComplete;

		void reset(void);

	  private:
		Output(Output const &src);
		Output &operator=(Output const &rhs);
	};

  public:
	Context(void) {}

	Input  input;
	Output output;

	void reset(void);

  private:
	Context(Context const &src);
	Context &operator=(Context const &rhs);
};
} // namespace http

#endif // HTTPCONTEXT_HPP