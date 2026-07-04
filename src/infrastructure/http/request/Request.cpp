/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:26:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 02:47:02 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/Request.hpp"

namespace http {

void Request::StartLine::reset(void)
{
	method.clear();
	target.clear();
	query.clear();
	protocol.clear();
}
Request::Request() : headers(), contentLength(0), body() {}

void Request::reset(void)
{
	startLine.reset();
	headers.clear();
	contentLength = 0;
	body.reset();
}

} // namespace http
