/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IExecuteDynamicResource.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 22:51:39 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 22:51:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IEXECUTEDYNAMICRESOURCE_HPP
#define IEXECUTEDYNAMICRESOURCE_HPP

class IExecuteDynamicResource
{
  public:
	IExecuteDynamicResource(void);
	IExecuteDynamicResource(IExecuteDynamicResource const &src);
	~IExecuteDynamicResource(void);

	IExecuteDynamicResource &operator=(IExecuteDynamicResource const &rhs);

  private:
};

#endif // IEXECUTEDYNAMICRESOURCE_HPP