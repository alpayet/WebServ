/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 16:45:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

namespace http
{
	class IRouteAccessValidator;
	class UploadStaticResourceController;
	class Request;
	class Response;

	class Router
	{
	  public:
		Router(
			IRouteAccessValidator		   &routeAccessValidator,
			UploadStaticResourceController &uploadFileController
		);

		void route(Request const &request, Response &response);

	  private:
		Router(Router const &src);
		Router &operator=(Router const &rhs);

		IRouteAccessValidator &_routeAccessValidator;

		UploadStaticResourceController &_uploadFileController;
	};
} // namespace http

#endif // HTTPROUTER_HPP