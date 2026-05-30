/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileController.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:10:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 02:03:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/controllers/UploadFileController.hpp"

namespace http
{
	UploadFileController::UploadFileController(void) {}

	void UploadFileController::operator()(const Request &request, Response &response) {}
} // namespace http
