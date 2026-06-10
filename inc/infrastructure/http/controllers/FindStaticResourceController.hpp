/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 19:43:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCECONTROLLER_HPP
#define FINDSTATICRESOURCECONTROLLER_HPP

namespace useCase
{
	class FindStaticResource;
} // namespace useCase

namespace http
{
	class Request;
	class Response;

	class FindStaticResourceController
	{
	  public:
		FindStaticResourceController(useCase::FindStaticResource &useCase);

		void operator()(Request const &request, Response &response);

	  private:
		FindStaticResourceController(FindStaticResourceController const &src);
		FindStaticResourceController &operator=(FindStaticResourceController const &rhs);

		useCase::FindStaticResource &_useCase;
	};
} // namespace http

#endif // FINDSTATICRESOURCECONTROLLER_HPP