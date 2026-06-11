/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:44:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP
#define EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"

namespace http
{
	struct Request;

	class ExecuteDynamicResourceDtoMapper
	{
	  public:
		static useCase::ExecuteDynamicResource::Input
		toDto(Request const &request, RoutePolicy const &routePolicy);

	  private:
		ExecuteDynamicResourceDtoMapper(void);
	};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP