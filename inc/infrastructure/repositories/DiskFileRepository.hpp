/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiskFileRepository.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 22:38:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:01:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISKFILEREPOSITORY_HPP
#define DISKFILEREPOSITORY_HPP

#include "domain/ports/IStaticResourceRepository.hpp"
#include <string>

class IResourceLocator;
class StaticResource;

class DiskFileRepository : public IStaticResourceRepository
{
  public:
	DiskFileRepository(IResourceLocator &resourceLocator);
	virtual ~DiskFileRepository(void) {}

	virtual void findById(std::string const &id, StaticResource &resource);
	virtual bool exists(std::string const &id);
	virtual void remove(std::string const &id);

  private:
	DiskFileRepository(DiskFileRepository const &src);
	DiskFileRepository &operator=(DiskFileRepository const &rhs);

	IResourceLocator &_resourceLocator;
};

#endif // DISKFILEREPOSITORY_HPP