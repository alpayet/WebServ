/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:20:50 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/19 22:55:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestFactory.hpp"
#include "HttpRequest.hpp"
#include <cstddef>

IRequest	*RequestFactory::createRequest(RequestType type)
{
	switch (type)
	{
		case RequestType_Http:
			return (new HttpRequest());
		default:
			return (NULL);
	}
}