/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileDto.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 02:38:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 02:38:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UploadFileDto.hpp"

UploadFileDto::UploadFileDto(void) {}

UploadFileDto::UploadFileDto(const UploadFileDto &src) { *this = src; }

UploadFileDto::~UploadFileDto(void) {}

UploadFileDto &UploadFileDto::operator=(UploadFileDto const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}