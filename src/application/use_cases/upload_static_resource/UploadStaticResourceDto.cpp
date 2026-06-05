/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceDto.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:50:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:50:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/upload_static_resource/UploadStaticResourceDto.hpp"

UploadStaticResourceDto::UploadStaticResourceDto(void) {}

UploadStaticResourceDto::UploadStaticResourceDto(const UploadStaticResourceDto &src)
{
	*this = src;
}

UploadStaticResourceDto::~UploadStaticResourceDto(void) {}

UploadStaticResourceDto &UploadStaticResourceDto::operator=(UploadStaticResourceDto const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}