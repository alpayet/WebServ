/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiskFileRepository.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 22:38:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/03 02:17:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISKFILEREPOSITORY_HPP
#define DISKFILEREPOSITORY_HPP

#include "domain/entities/StaticFile.hpp"
#include "domain/ports/IStaticFileRepository.hpp"
#include <string>

class IResourceLocator;
class DiskFileLockManager;

class DiskFileRepository : public IStaticFileRepository
{
  public:
	DiskFileRepository(IResourceLocator &resourceLocator);
	virtual ~DiskFileRepository(void) {}

	virtual void save(StaticFile const &file);

  private:
	DiskFileRepository(DiskFileRepository const &src);
	DiskFileRepository &operator=(DiskFileRepository const &rhs);

	IResourceLocator	&_resourceLocator;
	DiskFileLockManager &_diskFileLockManager;

	static void moveFile(std::string const &source, std::string const &destination);
	static void copyAndDelete(std::string const &source, std::string const &destination);
};

#endif // DISKFILEREPOSITORY_HPP