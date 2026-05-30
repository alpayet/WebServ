/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 01:56:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

namespace http
{
	class Router
	{
	  public:
		Router(UploadFileController &uploadFileController);

		void route(Request const &request, Response &response);

	  private:
		Router(Router const &src);
		Router &operator=(Router const &rhs);

		UploadFileController &_uploadFileController;
	};
} // namespace http

#endif // HTTPROUTER_HPP