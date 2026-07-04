/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:59:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCONTEXT_HPP
#define HTTPCONTEXT_HPP

#include "cgi/Parser.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Response.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include <vector>

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

		void reset(void);

	  private:
		Input(Input const &src);
		Input &operator=(Input const &rhs);
	};
	class Stream
	{
	  public:
		Stream(void);

		std::vector<char>  buf;
		cgi::Parser::State state;

		void reset(void);

	  private:
		Stream(Stream const &src);
		Stream &operator=(Stream const &rhs);
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
	Stream stream;
	Output output;

	void reset(void);

  private:
	Context(Context const &src);
	Context &operator=(Context const &rhs);
};
} // namespace http

#endif // HTTPCONTEXT_HPP