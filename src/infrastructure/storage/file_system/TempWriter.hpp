/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TempWriter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 02:38:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:25:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPFILESYSTEMWRITER_HPP
#define TEMPFILESYSTEMWRITER_HPP

#include <fstream>
#include <string>
#include <vector>

namespace webserv {
namespace fileSystem {
class TempWriter
{
  public:
	TempWriter(std::string const &tempFileName);
	~TempWriter(void);

	std::string const &getPath(void) const;
	int				   getFd(void) const;

	std::size_t write(std::vector<char> const &buf, std::size_t size);
	std::size_t write(std::vector<char> const &buf);

	bool exists(void) const;

	void resetPosition(void);
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
} // namespace webserv

#endif // TEMPFILESYSTEMWRITER_HPP