/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 23:24:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/controllers/ILimitsProvider.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"
#include <map>

namespace http {
ExecuteDynamicResourceController::ExecuteDynamicResourceController(
	app::useCase::ExecuteDynamicResource &useCase, ILimitsProvider &limitsProvider
)
	: _useCase(useCase), _limitsProvider(limitsProvider)
{}

void ExecuteDynamicResourceController::operator()(
	Request const &request, Response &response, RoutePolicy const &routePolicy
)
{
	std::string bodyPath;
	if (request.body.exists())
		bodyPath = request.body.getPath();

	if (request.contentLength > _limitsProvider.getMaxBodySize(request.target))
		throw Exception(Exception::bodyTooLarge);

	std::map<std::string, std::string> const &MetaVariables = createMetaVariables(request);

	app::useCase::ExecuteDynamicResource::Input dto =
		ExecuteDynamicResourceDtoMapper::toDto(request, routePolicy, bodyPath, MetaVariables);

	_useCase.execute(dto);
}

std::map<std::string, std::string>
ExecuteDynamicResourceController::createMetaVariables(Request const &request)
{
	std::map<std::string, std::string> metaVariable;

	metaVariable["REQUEST_METHOD"] = request.method;
	if (!request.query.empty())
		metaVariable["QUERY_STRING"] = request.query;

	std::map<std::string, std::string>::const_iterator content_length_it =
		request.headers.find(CONTENT_LENGTH);
	if (content_length_it != metaVariable.end())
		metaVariable["CONTENT_LENGTH"] = content_length_it->second;

	std::map<std::string, std::string>::const_iterator content_type_it =
		request.headers.find(CONTENT_TYPE);
	if (content_type_it != metaVariable.end())
		metaVariable["CONTENT_TYPE"] = content_type_it->second;
	return (metaVariable);
}
} // namespace http