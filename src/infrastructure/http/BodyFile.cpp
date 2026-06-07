/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:51:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 18:30:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/BodyFile.hpp"

namespace http
{
	char const BodyFile::_nameTemplate[] = "webserv_body";

	BodyFile::BodyFile(void) : _writer(_nameTemplate) {}

	void BodyFile::append(std::vector<char> const &data) { _writer.writeChunk(data); }

} // namespace http