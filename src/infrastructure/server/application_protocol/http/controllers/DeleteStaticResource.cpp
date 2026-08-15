/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:08:34 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/controllers/DeleteStaticResource.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"
#include "infrastructure/server/application_protocol/http/mappers/DeleteStaticResourceDto.hpp"
#include "infrastructure/server/application_protocol/http/presenters/DeleteStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"

namespace webserv {
namespace http {
namespace controller {

DeleteStaticResource::DeleteStaticResource(app::useCase::DeleteStaticResource &useCase)
	: _useCase(useCase)
{}

void DeleteStaticResource::operator()(Context &context, RoutePolicy const &routePolicy)
{
	app::useCase::DeleteStaticResource::Input const &dto =
		mapper::DeleteStaticResourceDto::toDto(context.input.state.request, routePolicy);

	presenter::DeleteStaticResource presenter;

	_useCase.execute(dto, presenter);

	presenter::DeleteStaticResource::ViewModel const &viewModel = presenter.getViewModel();
	context.output.response = viewModel.response;
}
} // namespace controller
} // namespace http
} // namespace webserv
