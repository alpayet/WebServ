/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourcePresenter.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 21:45:17 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEPRESENTER_HPP
#define DELETESTATICRESOURCEPRESENTER_HPP

class DeleteStaticResourcePresenter
{
  public:
	DeleteStaticResourcePresenter(void);
	DeleteStaticResourcePresenter(DeleteStaticResourcePresenter const &src);
	~DeleteStaticResourcePresenter(void);

	DeleteStaticResourcePresenter &operator=(DeleteStaticResourcePresenter const &rhs);

  private:
};

#endif // DELETESTATICRESOURCEPRESENTER_HPP