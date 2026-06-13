/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:07 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:15:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/TempWriter.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include <cstdlib>
#include <unistd.h>

namespace fileSystem {
char const TempWriter::_tmpDir[] = "/tmp/";

TempWriter::TempWriter(std::string const &tempFileName)
	: _tempFile(), _tempFileName(tempFileName), _tempFilePath()
{}

TempWriter::~TempWriter(void)
{
	if (std::remove(_tempFilePath.c_str()) != 0)
		throw Exception(Exception::internalErrorFileUnlinkFailed);
}

void TempWriter::writeChunk(std::vector<char> const &data)
{
	if (!_tempFile.is_open())
	{
		_tempFilePath = generateUniqueTempFile(_tempFileName);
		_tempFile.open(_tempFileName.c_str(), std::ios::binary);
		if (!_tempFile.is_open())
			throw Exception(Exception::internalErrorFileOpenFailed);
	}
	else if (!_tempFile.write(&data[0], data.size()))
		throw Exception(Exception::internalErrorFileWriteFailed);
}

std::string TempWriter::generateUniqueTempFile(std::string const &fileName)
{
	std::string unique_path((_tmpDir + fileName + "XXXXXX").c_str());

	int fd = mkstemp(&unique_path[0]);

	if (fd < 0)
		throw Exception(Exception::internalErrorFileOpenFailed);
	if (close(fd) < 0)
		throw Exception(Exception::internalErrorFileOpenFailed);
	return (unique_path);
}
} // namespace fileSystem
