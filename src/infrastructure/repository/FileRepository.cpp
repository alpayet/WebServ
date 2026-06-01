/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileRepository.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 23:37:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/02 00:27:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/repository/FileRepository.hpp"
#include "application/use_cases/UploadFileDto.hpp"
#include "infrastructure/repository/IResourceLocator.hpp"
#include <cstdio>

FileRepository::FileRepository(IResourceLocator &resourceLocator)
	: _resourceLocator(resourceLocator)
{
}

void FileRepository::save(const UploadFileDto &dto)
{
	std::string const &physical_path = _resourceLocator.resolvePhysicalPath(dto.target);
	// TODO : throw en cas derreur
	moveFile(dto.temporaryFilePath, physical_path);
}

void FileRepository::moveFile(std::string const &source, std::string const &destination)
{
	if (std::rename(source.c_str(), destination.c_str()))
}

void FileRepository::copyAndDelete(std::string const &source, std::string const &destination) {}
