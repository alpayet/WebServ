/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceUseCase.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 04:46:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

class DeleteStaticResourceInput;
class DeleteStaticResourceOutput;
class IStaticResourceLocator;
class IStaticResourceStorage;

class DeleteStaticResourceUseCase
{
  public:
	DeleteStaticResourceUseCase(
		IStaticResourceLocator &staticResourceLocator, IStaticResourceStorage &staticResourceStorage
	);

	DeleteStaticResourceOutput execute(DeleteStaticResourceInput const &dtoInput);

  private:
	DeleteStaticResourceUseCase(DeleteStaticResourceUseCase const &src);
	DeleteStaticResourceUseCase &operator=(DeleteStaticResourceUseCase const &rhs);

	IStaticResourceLocator &_staticResourceLocator;
	IStaticResourceStorage &_staticResourceStorage;
};

#endif // DELETESTATICRESOURCEUSECASE_HPP