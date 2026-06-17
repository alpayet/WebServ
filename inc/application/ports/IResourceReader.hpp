/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceReader.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:15:30 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 04:31:22 by alpayet          ###   ########.fr       */
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

	virtual std::vector<char> readChunk(void) = 0;
};
} // namespace app

#endif // IRESOURCEREADER_HPP