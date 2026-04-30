/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRequest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:09:15 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/30 21:17:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IREQUEST_HPP
# define IREQUEST_HPP

#include <string>

class IRequest
{
	public:
		enum MethodType
		{
			Get,
			Post,
			Delete,
			Unknown
		};

	public:
		virtual ~IRequest(void) {}

		virtual MethodType			getMethod(void) const = 0;
		virtual std::string const	&getTarget(void) const = 0;
		virtual std::string const	&getProtocol(void) const = 0;

		virtual IRequest	*clone(void) const = 0;
};

#endif