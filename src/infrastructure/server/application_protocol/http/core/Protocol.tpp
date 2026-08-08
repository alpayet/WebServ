/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Protocol.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 00:58:35 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/08 19:23:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLER_TPP
#define HTTPHANDLER_TPP

#include "infrastructure/server/application_protocol/http/exceptions/error_lookup.hpp"

namespace http {
template <class ExceptionType>
Protocol::PushStatus::Type Protocol::handleError(Context &context,
                                           ExceptionType const &e)
{
  Context::Output &context_output = context.output;
  unsigned short statusCode = to_status_code(e.getErrorCode());

  context.shouldKeepAlive = false;
  prepareDirectResponse(statusCode, context_output.response,
                        &context_output.reader);

  return (PushStatus::COMPLETE);
}

} // namespace http

#endif // HTTPHANDLER_TPP