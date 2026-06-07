/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceReader.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:15:30 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 00:58:27 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCEREADER_HPP
#define IRESOURCEREADER_HPP

#include <vector>

class IResourceReader
{
  public:
	virtual ~IResourceReader(void) {}

	virtual std::vector<char> readChunk(void) const = 0;
};

#endif // IRESOURCEREADER_HPP