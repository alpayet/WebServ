/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDataSource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:31:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 21:54:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/data_sources/FileDataSource.hpp"
#include "infrastructure/data_sources/DataSourcesException.hpp"

FileDataSource::FileDataSource(const std::string &filePath) : _filePath(filePath) {}

std::vector<char> FileDataSource::readChunk(void) const {}

std::string FileDataSource::getFilePath(void) const { return (_filePath); }