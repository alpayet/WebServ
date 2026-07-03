/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:07 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 22:26:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/TempWriter.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

namespace fileSystem {
char const TempWriter::TMP_DIRECTORY[] = "/tmp/";

TempWriter::TempWriter(std::string const &nameTemplate)
	: _fd(-1), _nameTemplate(nameTemplate), _tempFilePath()
{}

TempWriter::~TempWriter(void)
{
	if (_fd >= 0 && (std::remove(_tempFilePath.c_str()) < 0 || close(_fd) < 0))
		std::cerr << "Error : " << std::strerror(errno) << '\n';
}

std::string const &TempWriter::getTempFilePath(void) const { return (_tempFilePath); }

bool TempWriter::exists(void) const { return (_fd >= 0); }

std::size_t TempWriter::write(std::vector<char> const &buf, std::size_t const size)
{
	if (_fd < 0)
		generateUniqueTempFile();

	ssize_t bytes_written = ::write(_fd, &buf[0], size);
	if (bytes_written < 0)
		throw Exception(Exception::fileWriteFailed);

	return (bytes_written);
}

void TempWriter::generateUniqueTempFile(void)
{
	_tempFilePath += TMP_DIRECTORY;
	_tempFilePath += _nameTemplate;
	_tempFilePath += "XXXXXX";

	int fd = mkostemp(&_tempFilePath[0], O_CLOEXEC);
	if (fd < 0)
		throw Exception(Exception::fileOpenFailed);

	_fd = fd;
}

void TempWriter::reset(void)
{
	if (_fd >= 0)
	{
		if (ftruncate(_fd, 0) < 0)
			throw Exception(Exception::fileTruncateFailed);
		if (::lseek(_fd, 0, SEEK_SET) < 0)
			throw Exception(Exception::fileLseekFailed);
	}
}
} // namespace fileSystem
