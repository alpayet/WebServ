/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:51:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/03 22:56:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/BodyFile.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <cstdlib>

namespace http
{
	char const BodyFile::_pathTemplate[] = "/tmp/webserv_body_XXXXXX";

	void BodyFile::append(std::vector<char> const &data)
	{
		if (!_file.is_open())
		{
			_path = generateUniquePath();

			_file.open(_path.c_str(), std::ios::binary);
			if (!_file.is_open())
				throw Exception(Exception::bodyFileOpenFailed);
		}

		if (!_file.write(&data[0], data.size()))
			throw Exception(Exception::bodyFileOpenFailed);
	}

	std::string const &http::BodyFile::getPath() const { return (_path); }
	std::string		   BodyFile::generateUniquePath(void)
	{
		std::string unique_path(_pathTemplate);

		mkstemp(&unique_path[0]);
		return (unique_path);
	}
} // namespace http