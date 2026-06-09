/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:29:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 04:50:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPBODYFILE_HPP
#define HTTPBODYFILE_HPP

#include "infrastructure/storage/file_system/TempWriter.hpp"

namespace http
{
	class BodyFile
	{
	  public:
		BodyFile(void);

		void append(std::vector<char> const &data);

	  private:
		fileSystem::TempWriter _writer;

		static char const _nameTemplate[];
	};
} // namespace http

#endif // HTTPBODYFILE_HPP