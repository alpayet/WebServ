/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:17:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 22:51:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSESENDER_HPP
#define HTTPRESPONSESENDER_HPP

#include "infrastructure/http/Context.hpp"
#include <vector>

namespace http {

class IHttpVersionProvider;

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

	State produce(Context::Output &context);

  private:
	Sender(Sender const &src);
	Sender &operator=(Sender const &rhs);

	IHttpVersionProvider &_httpVersionProvider;
};
} // namespace response
} // namespace http

#endif // HTTPRESPONSESENDER_HPP