/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/01 18:23:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

namespace http
{
	class IRouteAccessValidator;
	class UploadFileController;
	class Request;
	class Response;

	class Router
	{
	  public:
		Router(
			IRouteAccessValidator &routeAccessValidator, UploadFileController &uploadFileController
		);

		void route(Request const &request, Response &response);

	  private:
		Router(Router const &src);
		Router &operator=(Router const &rhs);

		IRouteAccessValidator &_routeAccessValidator;

		UploadFileController &_uploadFileController;
	};
} // namespace http

#endif // HTTPROUTER_HPP