/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceController.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:09:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:42:22 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPUPLOADSTATICRESOURCECONTROLLER_HPP
#define HTTPUPLOADSTATICRESOURCECONTROLLER_HPP

class UploadStaticResourceUseCase;

namespace http
{
	class Request;
	class Response;

	class UploadStaticResourceController
	{
	  public:
		UploadStaticResourceController(UploadStaticResourceUseCase &uploadFileUseCase);

		void operator()(Request const &request, Response &response);

	  private:
		UploadStaticResourceController(UploadStaticResourceController const &src);
		UploadStaticResourceController &operator=(UploadStaticResourceController const &rhs);

		UploadStaticResourceUseCase &_uploadFileUseCase;
	};

} // namespace http

#endif // HTTPUPLOADSTATICRESOURCECONTROLLER_HPP