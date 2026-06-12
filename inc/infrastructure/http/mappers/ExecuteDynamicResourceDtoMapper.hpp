/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:19:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP
#define EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"

namespace http {
struct Request;

class ExecuteDynamicResourceDtoMapper
{
  public:
	static app::useCase::ExecuteDynamicResource::Input
	toDto(Request const &request, app::RoutePolicy const &routePolicy);

  private:
	ExecuteDynamicResourceDtoMapper(void);
};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP