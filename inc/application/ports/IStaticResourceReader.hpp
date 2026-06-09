/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourceReader.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:15:30 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 21:55:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICRESOURCEREADER_HPP
#define ISTATICRESOURCEREADER_HPP

#include <vector>

class IStaticResourceReader
{
  public:
	virtual ~IStaticResourceReader(void) {}

	virtual std::vector<char> readChunk(void) = 0;
};

#endif // ISTATICRESOURCEREADER_HPP