/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdReader.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:36:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 04:28:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/fdReader.hpp"

namespace fileSystem {
fdReader::fdReader(int const fd) : _fd(fd) {}

std::vector<char> fdReader::readChunk(void) {}
} // namespace fileSystem
