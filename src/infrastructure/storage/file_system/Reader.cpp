/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 03:39:58 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Reader.hpp"

namespace fileSystem {
Reader::Reader(std::string const &path) : _file(), _path(path) {}

std::vector<char> Reader::readChunk(void) { return std::vector<char>(); }
} // namespace fileSystem
