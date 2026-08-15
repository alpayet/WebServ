/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success_lookup.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:37:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:15:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/presenters/success_lookup.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include <cstdlib>

namespace webserv {
namespace http {
unsigned short to_status_code(app::ResourceStatus status)
{
	switch (status)
	{
		case app::FOUND:
			return (200);
		case app::DELETED:
			return (204);
		default:
			return (500);
	}
}
} // namespace http
} // namespace webserv
