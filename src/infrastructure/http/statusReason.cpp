/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statusReason.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:44:04 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 00:00:03 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/statusReason.hpp"

namespace http {
char const *getReasonPhrase(unsigned short statusCode)
{
	switch (statusCode)
	{
		case 200:
			return ("OK");
		case 204:
			return ("No Content");
		default:
			return ("");
	}
}
} // namespace http
