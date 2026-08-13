/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:17:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/14 01:03:52 by alpayet          ###   ########.fr       */
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
		HEADER_BLOCK,
		BODY,
		RESOURCE,
		COMPLETE
	};

	struct State
	{
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
	Sender(IHttpVersionProvider const &httpVersionProvider);

	Step produce(
		std::vector<char>	 &outputBuf,
		Response			 &response,
		app::IResourceReader *reader,
		bool				  shouldKeepAlive,
		State				 &state
	);

  private:
	Sender(Sender const &src);
	Sender &operator=(Sender const &rhs);

	IHttpVersionProvider const &_httpVersionProvider;
};
} // namespace response
} // namespace http

#endif // HTTPRESPONSESENDER_HPP