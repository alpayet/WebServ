/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success_lookup.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:37:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 00:51:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/success_lookup.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <cstdlib>

namespace http {
static std::pair<app::ResourceStatus, unsigned short> const LOOKUP_DATA[] = {
	std::make_pair(app::found, 200), std::make_pair(app::deleted, 204)
};

static std::size_t const LOOKUP_DATA_SIZE = sizeof(LOOKUP_DATA) / sizeof(LOOKUP_DATA[0]);

std::map<app::ResourceStatus, unsigned short> const
	SUCCESS_LOOKUP(LOOKUP_DATA, LOOKUP_DATA + LOOKUP_DATA_SIZE);

unsigned short toHttpCode(app::ResourceStatus const status)
{
	std::map<app::ResourceStatus, unsigned short>::const_iterator it = SUCCESS_LOOKUP.find(status);

	if (it == SUCCESS_LOOKUP.end())
		throw Exception(Exception::toHttpCodeFailed);
	return (it->second);
}
} // namespace http
