/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:46:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCECONTROLLER_HPP
#define FINDSTATICRESOURCECONTROLLER_HPP

class FindStaticResourceController
{
  public:
	FindStaticResourceController(void);
	FindStaticResourceController(FindStaticResourceController const &src);
	~FindStaticResourceController(void);

	FindStaticResourceController &operator=(FindStaticResourceController const &rhs);

  private:
};

#endif // FINDSTATICRESOURCECONTROLLER_HPP