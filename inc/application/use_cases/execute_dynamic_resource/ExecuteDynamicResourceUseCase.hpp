/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceUseCase.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 22:04:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

class ExecuteDynamicResourceInput;
class ExecuteDynamicResourceOutput;
class IDynamicResourceExecutor;

class ExecuteDynamicResourceUseCase
{
  public:
	ExecuteDynamicResourceUseCase(IDynamicResourceExecutor &dynamicResourceExecutor);

	ExecuteDynamicResourceOutput execute(ExecuteDynamicResourceInput const &dtoInput);

  private:
	ExecuteDynamicResourceUseCase(ExecuteDynamicResourceUseCase const &src);
	ExecuteDynamicResourceUseCase &operator=(ExecuteDynamicResourceUseCase const &rhs);

	IDynamicResourceExecutor &_dynamicResourceExecutor;
};

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP