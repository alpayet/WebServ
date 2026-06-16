/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourcePresenter.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 21:45:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEPRESENTER_HPP
#define EXECUTEDYNAMICRESOURCEPRESENTER_HPP

class ExecuteDynamicResourcePresenter
{
  public:
	ExecuteDynamicResourcePresenter(void);
	ExecuteDynamicResourcePresenter(ExecuteDynamicResourcePresenter const &src);
	~ExecuteDynamicResourcePresenter(void);

	ExecuteDynamicResourcePresenter &operator=(ExecuteDynamicResourcePresenter const &rhs);

  private:
};

#endif // EXECUTEDYNAMICRESOURCEPRESENTER_HPP