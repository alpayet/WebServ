/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceDtoMapper.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:08:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEDTOMAPPER_HPP
#define FINDSTATICRESOURCEDTOMAPPER_HPP

struct FindStaticResourceInput;

namespace http
{
	struct Request;

	class FindStaticResourceDtoMapper
	{
	  public:
		static FindStaticResourceInput toDto(Request const &request);

	  private:
		FindStaticResourceDtoMapper(void);
	};
} // namespace http

#endif // FINDSTATICRESOURCEDTOMAPPER_HPP