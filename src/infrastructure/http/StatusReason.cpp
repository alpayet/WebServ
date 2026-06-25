/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusReason.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:44:04 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 22:01:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/StatusReason.hpp"

namespace http {
char const *getReasonPhrase(unsigned short statusCode)
{
	switch (statusCode)
	{
		case 200:
			return (REASON_200);
		default:
			return (NO_REASON);
	}
}
} // namespace http
