/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:29:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 04:51:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMSTORAGE_HPP
#define FILESYSTEMSTORAGE_HPP

#include "application/ports/IStaticResourceStorage.hpp"
#include <string>

namespace fileSystem
{
	class Storage : public IStaticResourceStorage
	{
	  public:
		virtual ~Storage(void) {}

		virtual void			 remove(std::string const &storageLocation);
		virtual IResourceReader *createReader(std::string const &storageLocation);

	  private:
		Storage(Storage const &src);
		Storage &operator=(Storage const &rhs);
	};
} // namespace fileSystem

#endif // FILESYSTEMSTORAGE_HPP