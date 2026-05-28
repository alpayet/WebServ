/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:51:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/28 03:48:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/BodyFile.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <cstdlib>

namespace http
{
	char const BodyFile::_pathTemplate[] = "/tmp/webserv_body_XXXXXX";

	void BodyFile::append(const std::vector<char> &data)
	{
		if (!this->_file.is_open())
		{
			this->_path = generateUniquePath();
			this->_file.open(this->_path.c_str());
			if (!this->_file.is_open())
				throw Exception(Exception::bodyFileOpenFailed);
		}

		if (!this->_file.write(&data[0], data.size()))
			throw Exception(Exception::bodyFileOpenFailed);
	}

	std::string BodyFile::generateUniquePath(void)
	{
		std::string unique_path(_pathTemplate);

		mkstemp(&unique_path[0]);
		return (unique_path);
	}
} // namespace http