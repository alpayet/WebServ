/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceController.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/05 03:29:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/controllers/ServeStaticResourceController.hpp"
#include "application/ports/IResourceReader.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"
#include "infrastructure/server/application_protocol/http/mappers/ServeStaticResourceDtoMapper.hpp"
#include "infrastructure/server/application_protocol/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"

namespace http {
ServeStaticResourceController::ServeStaticResourceController(
	app::useCase::ServeStaticResource &useCase
)
	: _useCase(useCase)
{}

void ServeStaticResourceController::operator()(Context &context, RoutePolicy const &routePolicy)
{
	app::useCase::ServeStaticResource::Input const &dto =
		ServeStaticResourceDtoMapper::toDto(context.input.state.request, routePolicy);

	ServeStaticResourcePresenter presenter;

	_useCase.execute(dto, presenter);

	ServeStaticResourcePresenter::ViewModel const &viewModel = presenter.getViewModel();
	context.output.response = viewModel.response;
	delete (context.output.reader);
	context.output.reader = viewModel.reader;
}
} // namespace http