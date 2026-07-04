/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceReader.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:15:30 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:36:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCEREADER_HPP
#define IRESOURCEREADER_HPP

#include <vector>

namespace app {
class IResourceReader
{
  public:
	virtual ~IResourceReader(void) {}

	virtual std::size_t read(std::vector<char> &buf, std::size_t size) = 0;
	virtual std::size_t readChunk(std::vector<char> &buf) = 0;
};
} // namespace app

#endif // IRESOURCEREADER_HPP