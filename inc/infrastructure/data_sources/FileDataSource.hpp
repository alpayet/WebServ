/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDataSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:15:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDATASOURCE_HPP
#define FILEDATASOURCE_HPP

#include "domain/ports/IDataSource.hpp"
#include <string>

class FileDataSource : public IDataSource
{
  public:
	FileDataSource(std::string const &filePath);
	virtual ~FileDataSource(void) {}

	virtual std::vector<char> readChunk(void) const;

	std::string getFilePath(void) const;

  private:
	std::string _filePath;
};

#endif // FILEDATASOURCE_HPP