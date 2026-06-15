/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDeleteStaticResourcePresenter.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 21:47:46 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 21:49:23 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDELETESTATICRESOURCEPRESENTER_HPP
#define IDELETESTATICRESOURCEPRESENTER_HPP

class IDeleteStaticResourcePresenter
{
  public:
	IDeleteStaticResourcePresenter(void);
	IDeleteStaticResourcePresenter(IDeleteStaticResourcePresenter const &src);
	~IDeleteStaticResourcePresenter(void);

	IDeleteStaticResourcePresenter &operator=(IDeleteStaticResourcePresenter const &rhs);

  private:
};

#endif // IDELETESTATICRESOURCEPRESENTER_HPP