/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileRepository.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 23:37:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 00:58:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/UploadFileDto.hpp"
#include "infrastructure/repositories/DiskFileLockManager.hpp"
#include "infrastructure/repositories/DiskFileRepository.hpp"
#include "infrastructure/repositories/IResourceLocator.hpp"
#include <cstdio>

DiskFileRepository::DiskFileRepository(
	IResourceLocator &resourceLocator, DiskFileLockManager &diskFileLockManager
)
	: _resourceLocator(resourceLocator), _diskFileLockManager(diskFileLockManager)

{
}

void DiskFileRepository::save(StaticResource const &file)
{
	std::string const &physical_path = _resourceLocator.resolvePhysicalPath(file.getId());
	// TODO : throw en cas derreur
	moveFile(dto.temporaryFilePath, physical_path);
}

void FileRepository::moveFile(std::string const &source, std::string const &destination)
{
	if (std::rename(source.c_str(), destination.c_str()))
}

void FileRepository::copyAndDelete(std::string const &source, std::string const &destination) {}
