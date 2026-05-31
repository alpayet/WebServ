/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileController.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:10:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 04:18:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/UploadFileController.hpp"
#include "application/use_cases/UploadFileUseCase.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "mappers/UploadFileDtoMapper.hpp"

namespace http
{
	UploadFileController::UploadFileController(UploadFileUseCase &uploadFileUseCase)
		: _uploadFileUseCase(uploadFileUseCase)
	{
	}

	void UploadFileController::operator()(const Request &request, Response &response)
	{
		UploadFileDto dto = UploadFileDtoMapper::toDto(request);

		_uploadFileUseCase.execute(dto);
	}
} // namespace http
