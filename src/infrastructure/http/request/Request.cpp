/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:26:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 02:10:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/Request.hpp"

namespace http {
Request::Request() : headers(), method(), target(), protocol(), query(), contentLength(0), body() {}

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
