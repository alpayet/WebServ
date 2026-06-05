/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 16:48:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCECONTROLLER_HPP
#define FINDSTATICRESOURCECONTROLLER_HPP

namespace http
{
	class FindStaticResourceController
	{
	  public:
		FindStaticResourceController(void);
		FindStaticResourceController(FindStaticResourceController const &src);
		~FindStaticResourceController(void);

		FindStaticResourceController &operator=(FindStaticResourceController const &rhs);

	  private:
	};
} // namespace http

#endif // FINDSTATICRESOURCECONTROLLER_HPP