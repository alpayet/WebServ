/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceUseCase.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 04:12:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEUSECASE_HPP
#define FINDSTATICRESOURCEUSECASE_HPP

class FindStaticResourceInput;
class FindStaticResourceOutput;
class IStaticResourceLocator;
class IStaticResourceStorage;

class FindStaticResourceUseCase
{
  public:
	FindStaticResourceUseCase(
		IStaticResourceLocator &staticResourceLocator, IStaticResourceStorage &staticResourceStorage
	);

	FindStaticResourceOutput execute(FindStaticResourceInput const &dtoInput);

  private:
	FindStaticResourceUseCase(FindStaticResourceUseCase const &src);
	FindStaticResourceUseCase &operator=(FindStaticResourceUseCase const &rhs);

	IStaticResourceLocator &_staticResourceLocator;
	IStaticResourceStorage &_staticResourceStorage;
};

#endif // FINDSTATICRESOURCEUSECASE_HPP