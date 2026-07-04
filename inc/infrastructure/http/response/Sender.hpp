/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:17:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 04:30:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSESENDER_HPP
#define HTTPRESPONSESENDER_HPP

#include <vector>

namespace app {
class IResourceReader;
} // namespace app

namespace http {

class IHttpVersionProvider;
class Response;

namespace response {
class Sender
{
  public:
	enum Step
	{
		HeaderBlock,
		body,
		resource,
		cgi,
		complete
	};

	class State
	{
	  public:
		State(void);

		Step			  step;
		std::size_t		  totalBytesRead;
		std::vector<char> cgiBuf;

		void reset(void);

	  private:
		State(State const &src);
		State &operator=(State const &rhs);
	};

  public:
	Sender(IHttpVersionProvider &httpVersionProvider);

	Step produce(
		std::vector<char>	 &outputBuf,
		Response const		 &response,
		app::IResourceReader *reader,
		State				 &state
	);

  private:
	Sender(Sender const &src);
	Sender &operator=(Sender const &rhs);

	IHttpVersionProvider &_httpVersionProvider;
};
} // namespace response
} // namespace http

#endif // HTTPRESPONSESENDER_HPP