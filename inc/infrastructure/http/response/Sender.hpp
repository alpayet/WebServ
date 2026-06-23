/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 03:17:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 05:01:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSESENDER_HPP
#define HTTPRESPONSESENDER_HPP

#include "infrastructure/http/Context.hpp"
#include <vector>

namespace http {
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
	static State produce(std::vector<char> &outputBuf, Context::Output &context);

  private:
	Sender(Sender const &src);
	Sender &operator=(Sender const &rhs);
};
} // namespace response
} // namespace http

#endif // HTTPRESPONSESENDER_HPP