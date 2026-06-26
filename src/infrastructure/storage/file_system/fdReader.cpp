/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdReader.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 03:50:22 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/fdReader.hpp"

namespace fileSystem {
fdReader::fdReader(int const fd) : _fd(fd) {}

std::vector<char> fdReader::readChunk(void) { return (std::vector<char>()); }
} // namespace fileSystem
