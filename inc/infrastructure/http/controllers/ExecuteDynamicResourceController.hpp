/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 19:41:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCECONTROLLER_HPP
#define EXECUTEDYNAMICRESOURCECONTROLLER_HPP

namespace useCase
{
	class ExecuteDynamicResource;
} // namespace useCase

namespace http
{
	class Request;
	class Response;

	class ExecuteDynamicResourceController
	{
	  public:
		ExecuteDynamicResourceController(useCase::ExecuteDynamicResource &useCase);

		void operator()(Request const &request, Response &response);

	  private:
		ExecuteDynamicResourceController(ExecuteDynamicResourceController const &src);
		ExecuteDynamicResourceController &operator=(ExecuteDynamicResourceController const &rhs);

		useCase::ExecuteDynamicResource &_useCase;
	};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCECONTROLLER_HPP