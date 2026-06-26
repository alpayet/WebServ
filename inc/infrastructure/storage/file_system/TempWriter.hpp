/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:38:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 02:29:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPFILESYSTEMWRITER_HPP
#define TEMPFILESYSTEMWRITER_HPP

#include <fstream>
#include <string>
#include <vector>

namespace fileSystem {
class TempWriter
{
  public:
	TempWriter(std::string const &tempFileName);
	~TempWriter(void);

	std::string getTempFilePath(void) const;
	bool		exists(void) const;

	void writeChunk(std::vector<char> const &data);

  private:
	TempWriter(TempWriter const &src);
	TempWriter &operator=(TempWriter const &rhs);

	std::ofstream _tempFile;
	std::string	  _tempFileName;
	std::string	  _tempFilePath;
	bool		  _exists;

	static char const TMP_DIRECTORY[];

	static std::string generateUniqueTempFile(std::string const &fileName);
};
} // namespace fileSystem

#endif // TEMPFILESYSTEMWRITER_HPP