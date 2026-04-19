/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:25:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/19 22:52:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTFACTORY_HPP
# define REQUESTFACTORY_HPP

class IRequest;

class RequestFactory
{
	public:
		enum RequestType
		{
			RequestType_Http,
			RequestType_Unknown
		};

	public:
		static IRequest *createRequest(RequestType type);

	private:
		RequestFactory(void) {}
};

#endif