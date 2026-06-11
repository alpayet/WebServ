/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceDtoMapper.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:45:19 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEDTOMAPPER_HPP
#define FINDSTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/find_static_resource/FindStaticResource.hpp"

namespace http
{
	struct Request;

	class FindStaticResourceDtoMapper
	{
	  public:
		static useCase::FindStaticResource::Input
		toDto(Request const &request, RoutePolicy const &routePolicy);

	  private:
		FindStaticResourceDtoMapper(void);
	};
} // namespace http

#endif // FINDSTATICRESOURCEDTOMAPPER_HPP