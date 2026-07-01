/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 00:00:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 00:21:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_TPP
#define RESPONSE_TPP

#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/exceptions/errorLookup.hpp"
#include "infrastructure/http/exceptions/generateDefaultBody.hpp"
#include <cstring>
#include <sstream>

namespace http {
template <typename ExceptionErrorCode>
Response &Response::Builder::buildError(ExceptionErrorCode const errorCode)
{
	unsigned short status_error_code = toStatusCode(errorCode);
	char const	  *default_body = generateDefaultBody(status_error_code);

	std::stringstream content_length_ss;
	content_length_ss << std::strlen(default_body);

	withStatusCode(status_error_code);
	withHeader(http::header::CONTENT_LENGTH, content_length_ss.str());
	withBody(default_body);

	return (_response);
}
} // namespace http

#endif // RESPONSE_TPP