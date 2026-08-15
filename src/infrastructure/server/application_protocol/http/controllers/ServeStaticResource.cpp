/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:09:24 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/controllers/ServeStaticResource.hpp"
#include "application/ports/IResourceReader.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"
#include "infrastructure/server/application_protocol/http/mappers/ServeStaticResourceDto.hpp"
#include "infrastructure/server/application_protocol/http/presenters/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"

namespace webserv {
namespace http {
namespace controller {
ServeStaticResource::ServeStaticResource(app::useCase::ServeStaticResource &useCase)
	: _useCase(useCase)
{}

void ServeStaticResource::operator()(Context &context, RoutePolicy const &routePolicy)
{
	app::useCase::ServeStaticResource::Input const &dto =
		mapper::ServeStaticResourceDto::toDto(context.input.state.request, routePolicy);

	presenter::ServeStaticResource presenter;

	_useCase.execute(dto, presenter);

	presenter::ServeStaticResource::ViewModel const &viewModel = presenter.getViewModel();
	context.output.response = viewModel.response;
	delete (context.output.reader);
	context.output.reader = viewModel.reader;
}
} // namespace controller
} // namespace http
} // namespace webserv
