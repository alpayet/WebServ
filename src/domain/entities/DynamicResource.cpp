/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:18:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 22:22:58 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/DynamicResource.hpp"

DynamicResource::DynamicResource(
	std::string const						 &id,
	std::string const						 &storagePath,
	std::map<std::string, std::string> const &environment
)
	: _id(id), _storagePath(storagePath), _environment(environment)
{
}

std::string const &DynamicResource::getId(void) const { return (_id); }

std::string const &DynamicResource::getstoragePath(void) const { return (_storagePath); }

std::map<std::string, std::string> const &DynamicResource::getEnvironment(void) const
{
	return (_environment);
}