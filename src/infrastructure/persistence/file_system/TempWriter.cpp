/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:07 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 17:57:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/persistence/file_system/TempWriter.hpp"
#include "infrastructure/persistence/file_system/Exception.hpp"
#include <cstdlib>
#include <unistd.h>

namespace fileSystem
{
	TempWriter::TempWriter(std::string const &tempFileName)
		: _tempFile(), _tempFileName(tempFileName), _tempFilePath()
	{
	}

	TempWriter::~TempWriter(void)
	{
		if (unlink(_tempFilePath.c_str()) != 0)
			throw Exception(Exception::fileUnlinkFailed);
	}

	void TempWriter::writeChunk(std::vector<char> const &data)
	{
		if (!_tempFile.is_open())
		{
			_tempFilePath = generateUniqueTempFile(_tempFileName);
			_tempFile.open(_tempFileName.c_str(), std::ios::binary);
			if (!_tempFile.is_open())
				throw Exception(Exception::fileOpenFailed);
		}
		else if (!_tempFile.write(&data[0], data.size()))
			throw Exception(Exception::fileWriteFailed);
	}

	std::string TempWriter::generateUniqueTempFile(std::string const &fileName)
	{
		std::string unique_path(("/tmp/" + fileName + "XXXXXX").c_str());

		int fd = mkstemp(&unique_path[0]);

		if (fd < 0)
			throw Exception(Exception::fileOpenFailed);
		if (close(fd) < 0)
			throw Exception(Exception::fileOpenFailed);
		return (unique_path);
	}
} // namespace fileSystem
