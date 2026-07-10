/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/09 00:15:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP
#define EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"

namespace http {
class Request;
struct RoutePolicy;

class ExecuteDynamicResourceDtoMapper
{
  public:
	static app::useCase::ExecuteDynamicResource::Input toDto(
		Request const							 &request,
		RoutePolicy const						 &routePolicy,
		std::string const						 &bodyPath,
		std::map<std::string, std::string> const &metaVariables
	);

  private:
	ExecuteDynamicResourceDtoMapper(void);
};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP