/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileController.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:10:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 16:48:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/upload_static_resource/UploadStaticResourceDto.hpp"
#include "application/use_cases/upload_static_resource/UploadStaticResourceUseCase.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/controllers/UploadStaticResourceController.hpp"

namespace http
{
	UploadStaticResourceController::UploadStaticResourceController(
		UploadStaticResourceUseCase &uploadFileUseCase
	)
		: _uploadFileUseCase(uploadFileUseCase)
	{
	}

	void UploadStaticResourceController::operator()(const Request &request, Response &response)
	{
		UploadStaticResourceDto dto = UploadStaticResourceDtoMapper::toDto(request);

		_uploadFileUseCase.execute(dto);
	}
} // namespace http
