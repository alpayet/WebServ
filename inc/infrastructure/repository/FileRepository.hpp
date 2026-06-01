/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileRepository.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 22:38:59 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/02 00:20:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEREPOSITORY_HPP
#define FILEREPOSITORY_HPP

#include "application/ports/IFileRepository.hpp"
#include <string>

class IResourceLocator;

class FileRepository : public IFileRepository
{
  public:
	FileRepository(IResourceLocator &resourceLocator);
	virtual ~FileRepository(void) {}

	virtual void save(UploadFileDto const &dto);

  private:
	FileRepository(FileRepository const &src);
	FileRepository &operator=(FileRepository const &rhs);

	IResourceLocator &_resourceLocator;

	static void moveFile(std::string const &source, std::string const &destination);
	static void copyAndDelete(std::string const &source, std::string const &destination);
};

#endif // FILEREPOSITORY_HPP