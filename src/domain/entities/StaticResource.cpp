/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 00:43:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"

StaticResource::StaticResource(const std::string &id, const std::string &storageLocation)
	: _id(id), _storageLocation(storageLocation)
{
}

std::string const &StaticResource::getId(void) const { return (_id); }

std::string const &StaticResource::getStorageLocation(void) const { return (_storageLocation); }
