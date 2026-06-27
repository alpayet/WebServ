/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:07 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 08:40:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/TempWriter.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

namespace fileSystem {
char const TempWriter::TMP_DIRECTORY[] = "/tmp/";

TempWriter::TempWriter(std::string const &tempFileName)
	: _tempFile(), _tempFileName(tempFileName), _tempFilePath(), _exists(false)
{}

TempWriter::~TempWriter(void)
{
	// TODO: faire un log derreur masi ne pas throw
	if (_exists)
		std::remove(_tempFilePath.c_str());
}

std::string const &TempWriter::getTempFilePath(void) const { return (_tempFilePath); }

bool TempWriter::exists(void) const { return (_exists); }

void TempWriter::writeChunk(std::vector<char> const &data)
{
	if (!_tempFile.is_open())
	{
		_tempFilePath = generateUniqueTempFile(_tempFileName);
		_tempFile.open(_tempFileName.c_str(), std::ios::binary);
		if (!_tempFile.is_open())
			throw Exception(Exception::internalErrorFileOpenFailed);
		_exists = true;
	}
	else if (!_tempFile.write(&data[0], data.size()))
		throw Exception(Exception::internalErrorFileWriteFailed);
}

std::string TempWriter::generateUniqueTempFile(std::string const &fileName)
{
	std::string unique_path((TMP_DIRECTORY + fileName + "XXXXXX").c_str());

	int fd = mkstemp(&unique_path[0]);

	if (fd < 0)
		throw Exception(Exception::internalErrorFileOpenFailed);
	if (close(fd) < 0)
		throw Exception(Exception::internalErrorFileOpenFailed);
	return (unique_path);
}

void TempWriter::reset(void)
{
	if (_tempFile.is_open())
	{
		_tempFile.close();
		_tempFile.clear();
		_tempFile.open(_tempFileName.c_str(), std::ios::binary);
	}
}
} // namespace fileSystem
