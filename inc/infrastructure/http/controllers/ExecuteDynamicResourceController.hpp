/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/08 22:20:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCECONTROLLER_HPP
#define EXECUTEDYNAMICRESOURCECONTROLLER_HPP

class ExecuteDynamicResourceUseCase;

namespace http
{
	class Request;
	class Response;

	class ExecuteDynamicResourceController
	{
	  public:
		ExecuteDynamicResourceController(ExecuteDynamicResourceUseCase &useCase);

		void operator()(Request const &request, Response &response);

	  private:
		ExecuteDynamicResourceController(ExecuteDynamicResourceController const &src);
		ExecuteDynamicResourceController &operator=(ExecuteDynamicResourceController const &rhs);

		ExecuteDynamicResourceUseCase &_useCase;
	};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCECONTROLLER_HPP