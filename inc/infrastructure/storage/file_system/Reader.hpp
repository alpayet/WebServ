/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:31:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:24:22 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMREADER_HPP
#define FILESYSTEMREADER_HPP

#include "application/ports/IResourceReader.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace fileSystem {
class Reader : public app::IResourceReader
{
  public:
	Reader(std::string const &path);
	Reader(int const fd);
	~Reader(void);

	virtual std::size_t read(std::vector<char> &buf, std::size_t size);
	virtual std::size_t readChunk(std::vector<char> &buf);

  private:
	Reader(Reader const &src);
	Reader &operator=(Reader const &rhs);

	int			_fd;
	std::string _path;

	static int openFile(std::string const &path);

	std::size_t readSize(std::vector<char> &buf, std::size_t size);
};
} // namespace fileSystem

#endif // FILESYSTEMREADER_HPP