/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileController.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:09:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 01:55:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPUPLOADFILECONTROLLER_HPP
#define HTTPUPLOADFILECONTROLLER_HPP

namespace http
{
	class UploadFileController
	{
	  public:
		UploadFileController(void);

		void operator()(Request const &request, Response &response);

	  private:
		UploadFileController(UploadFileController const &src);
		UploadFileController &operator=(UploadFileController const &rhs);
	};

} // namespace http

#endif // HTTPUPLOADFILECONTROLLER_HPP