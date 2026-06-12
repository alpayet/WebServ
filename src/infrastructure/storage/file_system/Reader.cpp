/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:15:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Reader.hpp"

namespace fileSystem {
Reader::Reader(std::string const &path) : _path(path), _file() {}

std::vector<char> fileSystem::Reader::readChunk(void) {}
} // namespace fileSystem
