/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileDtoMapper.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 02:32:50 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 02:46:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADFILEDTOMAPPER_HPP
#define UPLOADFILEDTOMAPPER_HPP

#include "application/use_cases/UploadFileDto.hpp"

namespace http
{
	struct Request;

	class UploadFileDtoMapper
	{
	  public:
		static UploadFileDto toDto(Request const &request);

	  private:
		UploadFileDtoMapper(void);
	};
} // namespace http

#endif // UPLOADFILEDTOMAPPER_HPP