/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDtoMapper.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:43:50 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEDTOMAPPER_HPP
#define DELETESTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"

struct RoutePolicy;

namespace http
{
	struct Request;

	class DeleteStaticResourceDtoMapper
	{
	  public:
		static useCase::DeleteStaticResource::Input
		toDto(Request const &request, RoutePolicy const &routePolicy);

	  private:
		DeleteStaticResourceDtoMapper(void);
	};
} // namespace http

#endif // DELETESTATICRESOURCEDTOMAPPER_HPP