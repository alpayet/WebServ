/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 00:58:35 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 06:22:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLER_TPP
#define HTTPHANDLER_TPP

#include "infrastructure/http/exceptions/error_lookup.hpp"

namespace http {
template <typename ExceptionType>
ITransfertHandler::ProcessingStatus Handler::handleError(int id, ExceptionType const &e)
{
	Context::Output &context_output = _contexts[id].output;
	unsigned short	 statusCode = to_status_code(e.getErrorCode());

	prepareDirectResponse(statusCode, context_output.response, &context_output.reader);

	return (ITransfertHandler::complete);
}

} // namespace http

#endif // HTTPHANDLER_TPP