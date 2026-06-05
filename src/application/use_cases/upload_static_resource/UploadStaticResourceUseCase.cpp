/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceUseCase.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 01:10:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/upload_static_resource/UploadStaticResourceUseCase.hpp"
#include "domain/ports/IStaticResourceRepository.hpp"

UploadStaticResourceUseCase::UploadStaticResourceUseCase(
	IStaticResourceRepository &staticFileRepository
)
	: _staticFileRepository(staticFileRepository)
{
}

void UploadStaticResourceUseCase::execute(const UploadStaticResourceDto &dto) {}