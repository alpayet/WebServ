/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 16:59:25 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Reader.hpp"

namespace fileSystem {
Reader::Reader(std::string const &path) : _file(), _path(path) {}

std::vector<char> fileSystem::Reader::readChunk(void) { return std::vector<char>(); }
} // namespace fileSystem
