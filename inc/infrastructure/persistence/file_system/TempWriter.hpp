/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:38:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 04:09:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPFILESYSTEMWRITER_HPP
#define TEMPFILESYSTEMWRITER_HPP

#include <fstream>
#include <string>
#include <vector>

namespace fileSystem
{
	class TempWriter
	{
	  public:
		TempWriter(std::string const &tempFileName);
		~TempWriter(void);

		void writeChunk(std::vector<char> const &data);

	  private:
		TempWriter(TempWriter const &src);
		TempWriter &operator=(TempWriter const &rhs);

		std::ofstream	  _tempFile;
		std::string const _tempFileName;
		std::string		  _tempFilePath;

		static std::string generateUniqueFile(char const *pathTemplate);
	};
} // namespace fileSystem

#endif // TEMPFILESYSTEMWRITER_HPP