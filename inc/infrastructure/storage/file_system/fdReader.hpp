/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdReader.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:31:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 04:30:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMFDREADER_HPP
#define FILESYSTEMFDREADER_HPP

#include "application/ports/IResourceReader.hpp"
#include <string>
#include <vector>

namespace fileSystem {
class fdReader : public app::IResourceReader
{
  public:
	fdReader(int const fd);

	virtual std::vector<char> readChunk(void);

  private:
	fdReader(fdReader const &src);
	fdReader &operator=(fdReader const &rhs);

	int _fd;
};
} // namespace fileSystem

#endif // FILESYSTEMFDREADER_HPP