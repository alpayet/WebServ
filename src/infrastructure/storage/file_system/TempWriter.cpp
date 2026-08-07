/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:07 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:33:25 by alpayet          ###   ########.fr       */
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
	: _fd(-1), _nameTemplate(nameTemplate), _path()
{}

TempWriter::~TempWriter(void)
{
	if (_fd >= 0 && (std::remove(_path.c_str()) < 0 || close(_fd) < 0))
		std::cerr << "Error : " << std::strerror(errno) << '\n';
}

std::string const &TempWriter::getPath(void) const { return (_path); }
int				   TempWriter::getFd(void) const { return (_fd); }

bool TempWriter::exists(void) const { return (_fd >= 0); }

std::size_t TempWriter::write(std::vector<char> const &buf, std::size_t size)
{
	if (_fd < 0)
		generateUniqueTempFile();

	ssize_t bytes_written = ::write(_fd, &buf[0], size);
	if (bytes_written < 0)
		throw Exception(Exception::WRITE_FAILED);

	return (bytes_written);
}

std::size_t TempWriter::write(std::vector<char> const &buf)
{
	if (_fd < 0)
		generateUniqueTempFile();

	ssize_t bytes_written = ::write(_fd, &buf[0], buf.size());
	if (bytes_written < 0)
		throw Exception(Exception::WRITE_FAILED);

	return (bytes_written);
}

void TempWriter::generateUniqueTempFile(void)
{
	_path += TMP_DIRECTORY;
	_path += _nameTemplate;
	_path += "XXXXXX";

	int fd = mkostemp(&_path[0], O_CLOEXEC);
	if (fd < 0)
		throw Exception(Exception::OPEN_FAILED);

	_fd = fd;
}

void TempWriter::resetPosition(void)
{
	if (_fd >= 0 && ::lseek(_fd, 0, SEEK_SET) < 0)
		throw Exception(Exception::LSEEK_FAILED);
}

void TempWriter::reset(void)
{
	if (_fd >= 0)
	{
		if (ftruncate(_fd, 0) < 0)
			throw Exception(Exception::TRUNCATE_FAILED);
		if (::lseek(_fd, 0, SEEK_SET) < 0)
			throw Exception(Exception::LSEEK_FAILED);
	}
}
} // namespace fileSystem
