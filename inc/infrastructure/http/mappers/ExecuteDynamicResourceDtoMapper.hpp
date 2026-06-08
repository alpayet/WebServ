/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/08 22:20:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP
#define EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP

struct ExecuteDynamicResourceInput;

namespace http
{
	struct Request;

	class ExecuteDynamicResourceDtoMapper
	{
	  public:
		static ExecuteDynamicResourceInput toDto(Request const &request);

	  private:
		ExecuteDynamicResourceDtoMapper(void);
	};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP