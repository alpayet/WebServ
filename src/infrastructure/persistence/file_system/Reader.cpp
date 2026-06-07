/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 03:36:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/persistence/file_system/Reader.hpp"

namespace fileSystem
{
	Reader::Reader(std::string const &path) : _path(path), _file() {}

	std::vector<char> Reader::Reader::readChunk() const {}
} // namespace fileSystem
