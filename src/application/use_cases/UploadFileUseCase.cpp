/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileUseCase.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/18 16:05:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UploadFileUseCase.hpp"

UploadFileUseCase::UploadFileUseCase(void)
{}

UploadFileUseCase::UploadFileUseCase(const UploadFileUseCase &src)
{
	*this = src;
}

UploadFileUseCase::~UploadFileUseCase(void)
{}

UploadFileUseCase	&UploadFileUseCase::operator=(UploadFileUseCase const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}