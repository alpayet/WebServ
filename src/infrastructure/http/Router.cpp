/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:50:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 02:00:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Router.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/controllers/UploadFileController.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"

namespace http
{
	Router::Router(UploadFileController &uploadFileController)
		: _uploadFileController(uploadFileController)
	{
	}

	void Router::route(Request const &request, Response &response)
	{
		std::string const &method = request.method;
		// TODO: faire une methode "const Location& findLocation(std::string const &uri) const;"
		// TODO: faire egalement une methode "bool ismethodAllowed(std::string const &method)
		// cosnt;" de Location
		// if(location.ismethodAllowed())
		// 	throw Exception(Exception::methodNotAllowed);

		if (method == "GET")
		{
		}
		if (method == "POST")
		{
			// TODO: faire une methode bool hasUploadStore() const; de Location
			// if (!location.hasUploadStore())
			// 	throw Exception(Exception::methodNotAllowed);

			_uploadFileController(request, response);
		}
	}
} // namespace http
