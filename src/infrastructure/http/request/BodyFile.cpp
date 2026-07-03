/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:51:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 22:27:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/BodyFile.hpp"

namespace http {
namespace request {

char const BodyFile::NAME_TEMPLATE[] = "webserv_body";

BodyFile::BodyFile(void) : _writer(NAME_TEMPLATE) {}

std::size_t BodyFile::append(std::vector<char> const &data)
{
	return (_writer.write(data, data.size()));
}

std::size_t BodyFile::append(std::vector<char> const &data, std::size_t const size)
{
	return (_writer.write(data, size));
}

std::string const &BodyFile::getPath(void) const { return (_writer.getTempFilePath()); }

bool BodyFile::exists(void) const { return (_writer.exists()); }

void BodyFile::reset(void) { _writer.reset(); }

} // namespace request
} // namespace http
