/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceDtoMapper.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 02:40:18 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:25:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/upload_static_resource/UploadStaticResourceDto.hpp"
#include "infrastructure/http/Request.hpp"

namespace http
{
	UploadStaticResourceDto UploadStaticResourceDtoMapper::toDto(const Request &request)
	{
		(UploadStaticResourceDto){
			.target = request.target, .temporaryFilePath = request.body.getPath()
		};
	}
} // namespace http