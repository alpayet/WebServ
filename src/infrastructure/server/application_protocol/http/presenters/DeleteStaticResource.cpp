/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:57:56 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:13:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/presenters/DeleteStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/presenters/success_lookup.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include <sstream>

namespace webserv {
namespace http {
namespace presenter {

DeleteStaticResource::ViewModel const &DeleteStaticResource::getViewModel(void) const
{
	return (_viewModel);
}

void DeleteStaticResource::presentDeletedResource(app::ResourceStatus status)
{
	Response::Builder response_builder;

	response_builder.withStatusLine(to_status_code(status));

	_viewModel.response = response_builder.build();
}
} // namespace presenter
}
} // namespace http
