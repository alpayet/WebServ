/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:04:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 16:12:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCONTEXT_HPP
#define HTTPCONTEXT_HPP

#include "infrastructure/ITransferContext.hpp"
#include "infrastructure/http/parsers/ParsingState.hpp"

namespace app {
class IResourceReader;
} // namespace app

namespace http {
class Context : public ITransferContext
{
  public:
	Context(void) {}

	ParsingState		  state;
	std::vector<char>	  rawHeaders;
	std::vector<char>	  rawbody;
	app::IResourceReader *reader;

  private:
	Context(Context const &src);
	Context &operator=(Context const &rhs);
};
} // namespace http

#endif // HTTPCONTEXT_HPP