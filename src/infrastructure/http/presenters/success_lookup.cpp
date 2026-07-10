/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success_lookup.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:37:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 05:28:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/success_lookup.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <cstdlib>

namespace http {
unsigned short to_status_code(app::ResourceStatus status)
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
