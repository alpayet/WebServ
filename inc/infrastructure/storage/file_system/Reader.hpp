/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:31:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 21:58:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMREADER_HPP
#define FILESYSTEMREADER_HPP

#include "application/ports/IStaticResourceReader.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace fileSystem
{
	class Reader : public IStaticResourceReader
	{
	  public:
		Reader(std::string const &path);

		virtual std::vector<char> readChunk(void);

	  private:
		Reader(Reader const &src);
		Reader &operator=(Reader const &rhs);

		std::ifstream _file;
		std::string	  _path;
	};
} // namespace fileSystem

#endif // FILESYSTEMREADER_HPP