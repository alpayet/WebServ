/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:28:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 04:06:21 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPARSER_HPP
#define CGIPARSER_HPP

#include "cgi/Response.hpp"
#include <vector>

namespace cgi {

class Parser
{
  public:
	enum Step
	{
		header,
		body,
		complete
	};

	class State
	{
	  public:
		State(void);

		Step	 step;
		Response response;

		void reset(void);

	  private:
		State(State const &src);
		State &operator=(State const &rhs);
	};

  public:
	static Step parse(std::vector<char> &inputBuf, State &state);

  private:
	Parser(Parser const &src);
	Parser &operator=(Parser const &rhs);
};
} // namespace cgi

#endif // CGIPARSER_HPP