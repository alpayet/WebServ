/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:18:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 00:20:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/DynamicResource.hpp"

DynamicResource::DynamicResource(
	std::string const						 &id,
	std::string const						 &storageLocation,
	std::map<std::string, std::string> const &environment
)
	: _id(id), _storageLocation(storageLocation), _environment(environment)
{
}

std::string const &DynamicResource::getId(void) const { return (_id); }

std::string const &DynamicResource::getStorageLocation(void) const { return (_storageLocation); }

std::map<std::string, std::string> const &DynamicResource::getEnvironment(void) const
{
	return (_environment);
}