/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 04:07:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/http/Context.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/controllers/ILimitsProvider.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"
#include "infrastructure/http/presenters/ExecuteDynamicResourcePresenter.hpp"
#include "infrastructure/http/request/Request.hpp"
#include <map>

namespace http {
ExecuteDynamicResourceController::ExecuteDynamicResourceController(
	app::useCase::ExecuteDynamicResource &useCase, ILimitsProvider &limitsProvider
)
	: _useCase(useCase), _limitsProvider(limitsProvider)
{}

void ExecuteDynamicResourceController::operator()(Context &context, RoutePolicy const &routePolicy)
{
	Request const &request = context.input.state.request;

	std::string bodyPath;
	if (request.body.exists())
		bodyPath = request.body.getPath();
	if (request.contentLength > _limitsProvider.getMaxBodySize(request.target))
		throw Exception(Exception::bodyTooLarge);
	std::map<std::string, std::string> const &MetaVariables = createMetaVariables(request);

	app::useCase::ExecuteDynamicResource::Input const &dto =
		ExecuteDynamicResourceDtoMapper::toDto(request, routePolicy, bodyPath, MetaVariables);

	ExecuteDynamicResourcePresenter presenter;

	_useCase.execute(dto, presenter);

	ExecuteDynamicResourcePresenter::ViewModel const &viewModel = presenter.getViewModel();
	context.output.response = viewModel.response;
}

std::map<std::string, std::string>
ExecuteDynamicResourceController::createMetaVariables(Request const &request)
{
	std::map<std::string, std::string> metaVariable;

	metaVariable[cgiMeta::REQUEST_METHOD] = request.method;
	if (!request.query.empty())
		metaVariable[cgiMeta::QUERY_STRING] = request.query;

	std::map<std::string, std::string>::const_iterator content_length_it =
		request.headers.find(header::LOWER_CONTENT_LENGTH);
	if (content_length_it != metaVariable.end())
		metaVariable[cgiMeta::CONTENT_LENGTH] = content_length_it->second;

	std::map<std::string, std::string>::const_iterator content_type_it =
		request.headers.find(header::LOWER_CONTENT_TYPE);
	if (content_type_it != metaVariable.end())
		metaVariable[cgiMeta::CONTENT_TYPE] = content_type_it->second;
	return (metaVariable);
}
} // namespace http