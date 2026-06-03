/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiskFileRepository.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 22:38:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 01:10:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISKFILEREPOSITORY_HPP
#define DISKFILEREPOSITORY_HPP

#include "domain/entities/StaticResource.hpp"
#include "domain/ports/IStaticResourceRepository.hpp"
#include <string>

class IResourceLocator;
class DiskFileLockManager;

class DiskFileRepository : public IStaticResourceRepository
{
  public:
	DiskFileRepository(
		IResourceLocator &resourceLocator, DiskFileLockManager &_diskFileLockManager
	);
	virtual ~DiskFileRepository(void) {}

	virtual void save(StaticResource const &file);

  private:
	DiskFileRepository(DiskFileRepository const &src);
	DiskFileRepository &operator=(DiskFileRepository const &rhs);

	IResourceLocator	&_resourceLocator;
	DiskFileLockManager &_diskFileLockManager;

	static void moveFile(std::string const &source, std::string const &destination);
	static void copyAndDelete(std::string const &source, std::string const &destination);
};

#endif // DISKFILEREPOSITORY_HPP