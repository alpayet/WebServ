/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDataSource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:31:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/02 19:42:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/data_sources/FileDataSource.hpp"
#include "infrastructure/data_sources/DataSourcesException.hpp"
#include <fstream>

std::vector<char> FileDataSource::readAll(void) const
{
	std::ifstream	  ifs(_filePath.c_str());
	std::vector<char> fileContents;

	if (!ifs.is_open())
		throw(DataSourcesException(DataSourcesException::fileOpenFailed));

	ifs.
}

std::string FileDataSource::getFilePath(void) const { return (_filePath); }