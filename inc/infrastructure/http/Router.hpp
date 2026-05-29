/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/29 02:03:35 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

namespace http
{
	struct Request;
	struct Response;

	class Router
	{
	  public:
		Router(void);
		Router(Router const &src);
		~Router(void);

		Router &operator=(Router const &rhs);

		void route(Request const &request, Response &response);

	  private:
	};
} // namespace http

#endif // HTTPROUTER_HPP