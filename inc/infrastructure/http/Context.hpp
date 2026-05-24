/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:04:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/24 23:09:27 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCONTEXT_HPP
#define HTTPCONTEXT_HPP

#include "infrastructure/ITransferContext.hpp"
#include "infrastructure/http/parsers/ParsingState.hpp"

namespace http
{
	class Context : public ITransferContext
	{
	  public:
		Context(void) {}
		ParsingState state;

	  private:
		Context(Context const &src) {}
		Context &operator=(Context const &rhs) {}
	};
} // namespace http

#endif // HTTPCONTEXT_HPP