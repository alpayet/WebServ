/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceDtoMapper.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 02:32:50 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:42:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADSTATICRESOURCEDTOMAPPER_HPP
#define UPLOADSTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/upload_static_resource/UploadStaticResourceDto.hpp"

namespace http
{
	struct Request;

	class UploadStaticResourceDtoMapper
	{
	  public:
		static UploadStaticResourceDto toDto(Request const &request);

	  private:
		UploadStaticResourceDtoMapper(void);
	};
} // namespace http

#endif // UPLOADSTATICRESOURCEDTOMAPPER_HPP