/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileSystemRepository.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 22:38:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 00:53:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMREPOSITORY_HPP
#define FILESYSTEMREPOSITORY_HPP

#include "application/ports/IStaticResourceReaderProvider.hpp"
#include "domain/repositories/IStaticResourceRepository.hpp"
#include <string>

class StaticResource;

namespace fileSystem
{
	class IResourceLocator;

	class Repository : public IStaticResourceRepository, public IStaticResourceReaderProvider
	{
	  public:
		Repository(IResourceLocator &resourceLocator);
		virtual ~Repository(void) {}

		virtual StaticResource findById(std::string const &id);
		virtual bool		   exists(std::string const &id);
		virtual void		   remove(std::string const &id);

		virtual IResourceReader *createReader(std::string const &storageLocation);

	  private:
		Repository(Repository const &src);
		Repository &operator=(Repository const &rhs);

		IResourceLocator &_resourceLocator;
	};
} // namespace fileSystem

#endif // FILESYSTEMREPOSITORY_HPP