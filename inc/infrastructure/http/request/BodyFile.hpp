/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyFile.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:29:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/28 03:47:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BODYFILE_HPP
#define BODYFILE_HPP

#include <fstream>
#include <string>
#include <vector>

namespace http
{
	class BodyFile
	{
	  public:
		BodyFile(void) {}

		void append(std::vector<char> const &data);

	  private:
		BodyFile(BodyFile const &src) {}
		BodyFile &operator=(BodyFile const &rhs) {}

		std::ofstream _file;
		std::string	  _path;

		static char const _pathTemplate[];

		static std::string generateUniquePath(void);
	};
} // namespace http

#endif // BODYFILE_HPP