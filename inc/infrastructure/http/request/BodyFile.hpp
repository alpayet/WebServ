/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:29:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 05:31:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTBODYFILE_HPP
#define HTTPREQUESTBODYFILE_HPP

#include "infrastructure/storage/file_system/TempWriter.hpp"

namespace http {
namespace request {

class BodyFile
{
  public:
	BodyFile(void);

	void append(std::vector<char> const &data);

	std::string const &getPath(void) const;
	bool			   exists(void) const;

	void reset(void);

  private:
	BodyFile(BodyFile const &src);
	BodyFile &operator=(BodyFile const &rhs);

	fileSystem::TempWriter _writer;

	static char const NAME_TEMPLATE[];
};
} // namespace request
} // namespace http

#endif // HTTPREQUESTBODYFILE_HPP