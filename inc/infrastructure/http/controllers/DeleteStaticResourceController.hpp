/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:31:58 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCECONTROLLER_HPP
#define FINDSTATICRESOURCECONTROLLER_HPP

class DeleteStaticResourceUseCase;

namespace http
{
	class Request;
	class Response;

	class DeleteStaticResourceController
	{
	  public:
		DeleteStaticResourceController(DeleteStaticResourceUseCase &useCase);

		void operator()(Request const &request, Response &response);

	  private:
		DeleteStaticResourceController(DeleteStaticResourceController const &src);
		DeleteStaticResourceController &operator=(DeleteStaticResourceController const &rhs);

		DeleteStaticResourceUseCase &_useCase;
	};
} // namespace http

#endif // FINDSTATICRESOURCECONTROLLER_HPP