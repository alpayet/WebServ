/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/08 22:24:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceInput.hpp"
#include "infrastructure/http/Request.hpp"

namespace http
{
	ExecuteDynamicResourceInput ExecuteDynamicResourceDtoMapper::toDto(const Request &request) {}
} // namespace http