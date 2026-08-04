/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateKeepAliveStatus.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:19:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:49:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/updateKeepAliveStatus.hpp"

namespace http {
void updateKeepAliveStatus(Context &context)
{
	std::string const &request_connection = context.input.state.request.getConnection();

	if (request_connection == "close")
		context.shouldKeepAlive = false;
	else if (request_connection == "keep-alive")
		context.shouldKeepAlive = true;
}
} // namespace http
