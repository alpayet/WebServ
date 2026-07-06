/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:38:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 23:20:42 by alpayet          ###   ########.fr       */
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

	std::string const &getPath(void) const;

	std::size_t write(std::vector<char> const &buf, std::size_t size);
	std::size_t write(std::vector<char> const &buf);

	bool exists(void) const;

	void reset(void);

  private:
	TempWriter(TempWriter const &src);
	TempWriter &operator=(TempWriter const &rhs);

	int			_fd;
	std::string _nameTemplate;
	std::string _path;

	static char const TMP_DIRECTORY[];

	void generateUniqueTempFile(void);
};
} // namespace fileSystem

#endif // TEMPFILESYSTEMWRITER_HPP