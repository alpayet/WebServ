/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileRequestDto.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:28:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/18 16:05:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UploadFileRequestDto.hpp"

UploadFileRequestDto::UploadFileRequestDto(void)
{}

UploadFileRequestDto::UploadFileRequestDto(const UploadFileRequestDto &src)
{
	*this = src;
}

UploadFileRequestDto::~UploadFileRequestDto(void)
{}

UploadFileRequestDto	&UploadFileRequestDto::operator=(UploadFileRequestDto const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}