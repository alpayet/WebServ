/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceDtoMapper.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:12:02 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResourceInput.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/mappers/FindStaticResourceDtoMapper.hpp"

namespace http
{
	FindStaticResourceInput FindStaticResourceDtoMapper::toDto(const Request &request)
	{
		(FindStaticResourceInput){.id = request.target};
	}
} // namespace http