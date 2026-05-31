/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileDtoMapper.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 02:40:18 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 03:47:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/UploadFileDtoMapper.hpp"
#include "infrastructure/http/Request.hpp"

namespace http
{
	UploadFileDto UploadFileDtoMapper::toDto(const Request &request)
	{
		(UploadFileDto){.target = request.target, .temporaryFilePath = request.body.getPath()};
	}
} // namespace http