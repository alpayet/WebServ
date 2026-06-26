/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:51:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 02:32:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/messages/BodyFile.hpp"

namespace http {
char const BodyFile::NAME_TEMPLATE[] = "webserv_body";

BodyFile::BodyFile(void) : _writer(NAME_TEMPLATE) {}

void BodyFile::append(std::vector<char> const &data) { _writer.writeChunk(data); }

std::string const &BodyFile::getPath(void) const { return (_writer.getTempFilePath()); }

bool BodyFile::exists(void) const { return (_writer.exists()); }

} // namespace http