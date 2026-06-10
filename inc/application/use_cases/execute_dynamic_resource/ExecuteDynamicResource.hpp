/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 17:52:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

class ExecuteDynamicResourceInput;
class ExecuteDynamicResourceOutput;
class IDynamicResourceExecutor;
class IDynamicResourceLocator;

namespace useCase
{
	class ExecuteDynamicResource
	{
	  public:
		ExecuteDynamicResource(
			IDynamicResourceExecutor &dynamicResourceExecutor,
			IDynamicResourceLocator	 &dynamicResourceLocator
		);

		ExecuteDynamicResourceOutput execute(ExecuteDynamicResourceInput const &dtoInput);

	  private:
		ExecuteDynamicResource(ExecuteDynamicResource const &src);
		ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

		IDynamicResourceLocator	 &_dynamicResourceLocator;
		IDynamicResourceExecutor &_dynamicResourceExecutor;
	};
} // namespace useCase

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP