/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_keep_alive_status.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:19:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:21:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/update_keep_alive_status.hpp"

namespace webserv {
namespace http {
void update_keep_alive_status(Context &context)
{
	std::string const &request_connection = context.input.state.request.getConnection();

	if (request_connection == "close")
		context.shouldKeepAlive = false;
	else if (request_connection == "keep-alive")
		context.shouldKeepAlive = true;
}
} // namespace http
}