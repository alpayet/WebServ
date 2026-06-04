/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiskFileRepository.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 23:37:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:04:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/repositories/DiskFileRepository.hpp"
#include "domain/entities/StaticResource.hpp"
#include "domain/ports/IDataSource.hpp"
#include "infrastructure/data_sources/FileDataSource.hpp"
#include "infrastructure/repositories/IResourceLocator.hpp"

DiskFileRepository::DiskFileRepository(IResourceLocator &resourceLocator)
	: _resourceLocator(resourceLocator)
{
}

void DiskFileRepository::findById(std::string const &id, StaticResource &resource)
{
	IDataSource *dataSource = new FileDataSource(_resourceLocator.resolvePhysicalPath(id));

	resource.init(id, dataSource);
}
