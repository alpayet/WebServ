/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/13 17:36:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/ports/IResourceReader.hpp"
#include "infrastructure/server/application_protocol/cgi/constants.hpp"
#include "infrastructure/server/application_protocol/constants.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ExecuteDynamicResource.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ILimitsProvider.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include "infrastructure/server/application_protocol/http/mappers/ExecuteDynamicResourceDto.hpp"
#include "infrastructure/server/application_protocol/http/presenters/ExecuteDynamicResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include <map>

namespace http {
namespace controller {

ExecuteDynamicResource::ExecuteDynamicResource(
    app::useCase::ExecuteDynamicResource &useCase,
    ILimitsProvider const &limitsProvider)
    : _useCase(useCase), _limitsProvider(limitsProvider) {}

void ExecuteDynamicResource::operator()(Context &context,
                                        RoutePolicy const &routePolicy) {
  Request const &request = context.input.state.request;

  std::string bodyPath;
  if (request.hasBody())
    bodyPath = request.getBodyPath();
  if (request.getContentLength() >
      _limitsProvider.getMaxBodySize(request.getTarget()))
    throw Exception(Exception::BODY_TOO_LARGE);
  std::map<std::string, std::string> const &MetaVariables =
      createMetaVariables(request);

  presenter::ExecuteDynamicResource presenter;

  app::useCase::ExecuteDynamicResource::Input const &dto =
      mapper::ExecuteDynamicResourceDto::toDto(request, routePolicy, bodyPath,
                                               MetaVariables);

  _useCase.execute(dto, presenter);

  presenter::ExecuteDynamicResource::ViewModel const &viewModel =
      presenter.getViewModel();
  context.stream.stream_info = viewModel.stream_info;
}

std::map<std::string, std::string>
ExecuteDynamicResource::createMetaVariables(Request const &request) {
  std::map<std::string, std::string> metaVariable;

  metaVariable[cgi::meta::REQUEST_METHOD] = request.getMethod();
  if (request.hasQuery())
    metaVariable[cgi::meta::QUERY_STRING] = request.getQuery();

  if (request.hasContentLength())
    metaVariable[cgi::meta::CONTENT_LENGTH] =
        request.getHeader(headers::CONTENT_LENGTH);

  if (request.hasHeader(headers::CONTENT_TYPE))
    metaVariable[cgi::meta::CONTENT_TYPE] =
        request.getHeader(headers::CONTENT_TYPE);
  if (request.hasHeader(headers::COOKIE))
    metaVariable[cgi::meta::HTTP_COOKIE] = request.getHeader(headers::COOKIE);
  return (metaVariable);
}
} // namespace controller

} // namespace http
