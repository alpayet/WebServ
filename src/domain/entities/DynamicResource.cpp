/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:18:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 01:11:17 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/DynamicResource.hpp"

DynamicResource::DynamicResource(std::string const &id, std::string const &storagePath)
	: _id(id), _storagePath(storagePath)
{
}

std::string const &DynamicResource::getId(void) const { return (_id); }

std::string const &DynamicResource::getstoragePath(void) const { return (_storagePath); }
