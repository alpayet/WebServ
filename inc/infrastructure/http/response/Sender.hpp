/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:17:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 04:13:13 by alpayet          ###   ########.fr       */
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
	enum State
	{
		HeaderBlock,
		body,
		resource,
		complete,
	};

  public:
	Sender(IHttpVersionProvider &httpVersionProvider);

	State produce(
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