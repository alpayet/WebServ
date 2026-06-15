/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 04:26:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP
#define EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"

namespace http {
struct Request;
class RoutePolicy;

class ExecuteDynamicResourceDtoMapper
{
  public:
	static app::useCase::ExecuteDynamicResource::Input ExecuteDynamicResourceDtoMapper::toDto(
		Request const							 &request,
		RoutePolicy const						 &routePolicy,
		std::string const						 &bodyPath,
		std::size_t const						  contentLength,
		std::size_t const						  maxBodySize,
		std::map<std::string, std::string> const &metaVariables
	);

  private:
	ExecuteDynamicResourceDtoMapper(void);
};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP