/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileUseCase.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/02 16:35:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/UploadFileUseCase.hpp"
#include "domain/ports/IStaticFileRepository.hpp"

UploadFileUseCase::UploadFileUseCase(
	IConfigProvider &configProvider, IStaticFileRepository &staticFileRepository
)
	: _configProvider(configProvider), _staticFileRepository(staticFileRepository)
{
}

void UploadFileUseCase::execute(const UploadFileDto &dto) {}