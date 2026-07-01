/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   successLookup.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:37:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 03:38:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/successLookup.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <cstdlib>

namespace http {
unsigned short toHttpStatusCode(app::ResourceStatus const status)
{
	switch (status)
	{
		case app::found:
			return (200);
		case app::deleted:
			return (204);
		default:
			return (500);
	}
}
} // namespace http
