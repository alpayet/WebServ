/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileController.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:09:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 04:05:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPUPLOADFILECONTROLLER_HPP
#define HTTPUPLOADFILECONTROLLER_HPP

class UploadFileUseCase;

namespace http
{
	class UploadFileController
	{
	  public:
		UploadFileController(UploadFileUseCase &uploadFileUseCase);

		void operator()(Request const &request, Response &response);

	  private:
		UploadFileController(UploadFileController const &src);
		UploadFileController &operator=(UploadFileController const &rhs);

		UploadFileUseCase &_uploadFileUseCase;
	};

} // namespace http

#endif // HTTPUPLOADFILECONTROLLER_HPP