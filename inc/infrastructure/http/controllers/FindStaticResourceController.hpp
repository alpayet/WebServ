/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:04:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCECONTROLLER_HPP
#define FINDSTATICRESOURCECONTROLLER_HPP

class FindStaticResourceUseCase;

namespace http
{
	class Request;
	class Response;

	class FindStaticResourceController
	{
	  public:
		FindStaticResourceController(FindStaticResourceUseCase &useCase);

		void operator()(Request const &request, Response &response);

	  private:
		FindStaticResourceController(FindStaticResourceController const &src);
		FindStaticResourceController &operator=(FindStaticResourceController const &rhs);

		FindStaticResourceUseCase &_useCase;
	};
} // namespace http

#endif // FINDSTATICRESOURCECONTROLLER_HPP