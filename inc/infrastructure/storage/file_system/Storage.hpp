/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:29:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 03:54:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMSTORAGE_HPP
#define FILESYSTEMSTORAGE_HPP

#include "application/ports/IStaticResourceStorage.hpp"
#include <string>

namespace fileSystem {
class Storage : public app::IStaticResourceStorage
{
  public:
	Storage(void) {}
	virtual ~Storage(void) {}

	virtual void				  remove(std::string const &resourcePath);
	virtual app::IResourceReader *createReader(std::string const &resourcePath);

	static bool		   exists(std::string const &path);
	static bool		   isRegularFile(std::string const &path);
	static bool		   isDirectory(std::string const &path);
	static bool		   isReadable(std::string const &path);
	static bool		   isWritable(std::string const &path);
	static bool		   isExecutable(std::string const &path);
	static std::size_t getSize(std::string const &path);
	static bool		   isDeletable(std::string const &path);

  private:
	Storage(Storage const &src);
	Storage &operator=(Storage const &rhs);
};
} // namespace fileSystem

#endif // FILESYSTEMSTORAGE_HPP