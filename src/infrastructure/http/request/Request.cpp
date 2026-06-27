/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:26:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 05:31:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/Request.hpp"

namespace http {
Request::Request() : contentLength(0) {}

void Request::reset(void)
{
	headers.clear();
	method.clear();
	target.clear();
	protocol.clear();
	query.clear();
	contentLength = 0;
	body.reset();
}

} // namespace http
