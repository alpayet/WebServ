/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:50:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/03 02:08:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/controllers/UploadFileController.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/router/IRouteAccessValidator.hpp"
#include <algorithm>

namespace http
{
	Router::Router(
		IRouteAccessValidator &routeAccessValidator, UploadFileController &uploadFileController
	)
		: _routeAccessValidator(routeAccessValidator), _uploadFileController(uploadFileController)
	{
	}

	void Router::route(Request const &request, Response &response)
	{
		std::string const			   &method = request.method;
		std::string const			   &target = request.target;
		std::vector<std::string> const &allowed_methods =
			_routeAccessValidator.getAllowedMethods(target);

		if (std::find(allowed_methods.begin(), allowed_methods.end(), method) ==
			allowed_methods.end())
			throw Exception(Exception::methodNotAllowed);

		if (method == "GET")
		{
		}
		if (method == "PUT")
		{
			_uploadFileController(request, response);
		}
		if (method == "POST")
		{
		}
	}
} // namespace http
