/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 04:24:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/router/RoutePolicy.hpp"

namespace http {
app::useCase::ExecuteDynamicResource::Input ExecuteDynamicResourceDtoMapper::toDto(
	Request const							 &request,
	RoutePolicy const						 &routePolicy,
	std::string const						 &bodyPath,
	std::size_t const						  contentLength,
	std::size_t const						  maxBodySize,
	std::map<std::string, std::string> const &metaVariables
)
{
	return (app::useCase::ExecuteDynamicResource::Input(
		request.target, routePolicy.rootPath, bodyPath, contentLength, maxBodySize, metaVariables
	));
}
} // namespace http