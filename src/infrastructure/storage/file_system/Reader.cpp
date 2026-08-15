/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:24:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Reader.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/constants.hpp"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

namespace webserv {
namespace fileSystem {
Reader::Reader(std::string const &path) : _fd(-1), _path(path), _shouldClose(true) {}

Reader::Reader(int const fd) : _fd(fd), _path(), _shouldClose(false) {}

Reader::~Reader(void)
{
	if (_shouldClose && _fd >= 0 && close(_fd) < 0)
		std::cerr << "Error : " << std::strerror(errno) << '\n';
}

std::size_t Reader::read(std::vector<char> &buf, std::size_t size)
{
	if (size >= CHUNCK_SIZE)
		return (readChunk(buf));
	return (readSize(buf, size));
}

std::size_t Reader::readSize(std::vector<char> &buf, std::size_t size)
{
	if (_fd < 0)
		_fd = openFile(_path);

	buf.resize(size);

	ssize_t bytes_read = ::read(_fd, &buf[0], size);
	if (bytes_read < 0)
		throw Exception(Exception::READ_FAILED);

	buf.resize(bytes_read);

	return (bytes_read);
}

std::size_t Reader::readChunk(std::vector<char> &buf)
{
	if (_fd < 0)
		_fd = openFile(_path);

	buf.resize(CHUNCK_SIZE);

	ssize_t bytes_read = ::read(_fd, &buf[0], CHUNCK_SIZE);
	if (bytes_read < 0)
		throw Exception(Exception::READ_FAILED);

	buf.resize(bytes_read);

	return (bytes_read);
}

int Reader::openFile(std::string const &path)
{
	int fd = open(path.c_str(), O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		throw Exception(Exception::OPEN_FAILED);
	return (fd);
}
} // namespace fileSystem
}
