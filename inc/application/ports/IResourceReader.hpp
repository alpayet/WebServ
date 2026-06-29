/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceReader.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:15:30 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 01:56:12 by alpayet          ###   ########.fr       */
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

	virtual std::size_t readChunck(std::vector<char> &buf) = 0;
};
} // namespace app

#endif // IRESOURCEREADER_HPP