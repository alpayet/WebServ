/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceUseCase.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 01:06:40 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

class ExecuteDynamicResourceInput;
class ExecuteDynamicResourceOutput;
class IDynamicResourceExecutor;
class IDynamicResourceLocator;

class ExecuteDynamicResourceUseCase
{
  public:
	ExecuteDynamicResourceUseCase(
		IDynamicResourceExecutor &dynamicResourceExecutor,
		IDynamicResourceLocator	 &dynamicResourceLocator
	);

	ExecuteDynamicResourceOutput execute(ExecuteDynamicResourceInput const &dtoInput);

  private:
	ExecuteDynamicResourceUseCase(ExecuteDynamicResourceUseCase const &src);
	ExecuteDynamicResourceUseCase &operator=(ExecuteDynamicResourceUseCase const &rhs);

	IDynamicResourceLocator	 &_dynamicResourceLocator;
	IDynamicResourceExecutor &_dynamicResourceExecutor;
};

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP