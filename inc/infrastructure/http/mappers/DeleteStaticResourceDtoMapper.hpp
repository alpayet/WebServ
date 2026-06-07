/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDtoMapper.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:34:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEDTOMAPPER_HPP
#define DELETESTATICRESOURCEDTOMAPPER_HPP

struct DeleteStaticResourceInput;

namespace http
{
	struct Request;

	class DeleteStaticResourceDtoMapper
	{
	  public:
		static DeleteStaticResourceInput toDto(Request const &request);

	  private:
		DeleteStaticResourceDtoMapper(void);
	};
} // namespace http

#endif // DELETESTATICRESOURCEDTOMAPPER_HPP