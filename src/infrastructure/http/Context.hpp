/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/03 16:16:12 by ludebion         ###   ########.fr       */
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
	struct Input
	{
		Input(void);

		std::vector<char>	   buf;
		request::Parser::State state;

		void reset(void);

	  private:
		Input(Input const &src);
		Input &operator=(Input const &rhs);
	};

	struct Stream
	{
		Stream(void);

		std::vector<char>  buf;
		cgi::Parser::State state;
		int				   localRedirDepth;

		static int const MAX_LOCAL_REDIR_DEPTH = 10;

		void reset(void);

	  private:
		Stream(Stream const &src);
		Stream &operator=(Stream const &rhs);
	};

	struct Output
	{
		Output(void);
		~Output(void);

		response::Sender::State state;
		Response				response;
		app::IResourceReader   *reader;

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
