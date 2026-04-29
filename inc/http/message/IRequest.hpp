/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRequest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:09:15 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/29 19:41:33 by alpayet          ###   ########.fr       */
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
			MethodType_Get,
			MethodType_Post,
			MethodType_Delete
		};

	public:
		virtual ~IRequest(void) {}

		virtual MethodType	getMethod(void) const = 0;
		virtual std::string	getTarget(void) const = 0;
		virtual std::string	getProtocol(void) const = 0;
};

#endif