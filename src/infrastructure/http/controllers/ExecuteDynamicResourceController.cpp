/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/11 20:53:34 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "application/ports/IResourceReader.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "cgi/constants.hpp"
#include "infrastructure/constants.hpp"
#include "infrastructure/http/Context.hpp"
#include "infrastructure/http/controllers/ILimitsProvider.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"
#include "infrastructure/http/request/Request.hpp"
#include <map>

namespace http {
ExecuteDynamicResourceController::ExecuteDynamicResourceController(
	app::useCase::ExecuteDynamicResource &useCase, const ILimitsProvider &limitsProvider
)
	: _useCase(useCase), _limitsProvider(limitsProvider)
{}

void ExecuteDynamicResourceController::operator()(Context &context, RoutePolicy const &routePolicy)
{
	Request const &request = context.input.state.request;

	std::string bodyPath;
	if (request.hasBody())
		bodyPath = request.getBodyPath();
	if (request.getContentLength() > _limitsProvider.getMaxBodySize(request.getTarget()))
		throw Exception(Exception::bodyTooLarge);
	std::map<std::string, std::string> const &MetaVariables = createMetaVariables(request);

	app::useCase::ExecuteDynamicResource::Input const &dto =
		ExecuteDynamicResourceDtoMapper::toDto(request, routePolicy, bodyPath, MetaVariables);

	_useCase.execute(dto);
}

std::map<std::string, std::string>
ExecuteDynamicResourceController::createMetaVariables(Request const &request)
{
	std::map<std::string, std::string> metaVariable;

	metaVariable[cgi::meta::REQUEST_METHOD] = request.getMethod();
	if (request.hasQuery())
		metaVariable[cgi::meta::QUERY_STRING] = request.getQuery();

	if (request.hasContentLength())
		metaVariable[cgi::meta::CONTENT_LENGTH] = request.getHeader(headers::CONTENT_TYPE);

	if (request.hasHeader(headers::CONTENT_TYPE))
		metaVariable[cgi::meta::CONTENT_TYPE] = request.getHeader(headers::CONTENT_TYPE);
	if (request.hasHeader(headers::COOKIE))
		metaVariable[cgi::meta::HTTP_COOKIE] = request.getHeader(headers::COOKIE);
	return (metaVariable);
}
} // namespace http