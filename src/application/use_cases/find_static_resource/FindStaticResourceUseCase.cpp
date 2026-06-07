/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceUseCase.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 00:19:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResourceUseCase.hpp"
#include "application/ports/IStaticResourceReaderProvider.hpp"
#include "domain/repositories/IStaticResourceRepository.hpp"

FindStaticResourceUseCase::FindStaticResourceUseCase(
	IStaticResourceRepository	  &staticResourceRepository,
	IStaticResourceReaderProvider &staticResourceReaderProvider
)
	: _staticResourceRepository(staticResourceRepository),
	  _staticResourceReaderProvider(staticResourceReaderProvider)
{
}

void FindStaticResourceUseCase::execute(const FindStaticResourceDto &dto) {}
