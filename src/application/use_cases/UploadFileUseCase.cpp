/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileUseCase.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 20:32:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/UploadFileUseCase.hpp"

UploadFileUseCase::UploadFileUseCase(
	IConfigProvider *configProvider, IFileRepository *fileRepository
)
	: _configProvider(configProvider), _fileRepository(fileRepository)
{
}

void UploadFileUseCase::execute(const UploadFileDto &dto) {}