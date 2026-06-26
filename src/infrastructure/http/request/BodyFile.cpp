/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:51:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 04:25:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/BodyFile.hpp"

namespace http {
namespace request {

char const BodyFile::NAME_TEMPLATE[] = "webserv_body";

BodyFile::BodyFile(void) : _writer(NAME_TEMPLATE) {}

void BodyFile::append(std::vector<char> const &data) { _writer.writeChunk(data); }

std::string const &BodyFile::getPath(void) const { return (_writer.getTempFilePath()); }

bool BodyFile::exists(void) const { return (_writer.exists()); }

} // namespace request
} // namespace http
