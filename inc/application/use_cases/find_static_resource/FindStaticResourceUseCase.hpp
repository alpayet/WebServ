/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceUseCase.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 20:07:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEUSECASE_HPP
#define FINDSTATICRESOURCEUSECASE_HPP

class FindStaticResourceInput;
class FindStaticResourceOutput;
class IStaticResourceRepository;
class IStaticResourceReaderProvider;

class FindStaticResourceUseCase
{
  public:
	FindStaticResourceUseCase(
		IStaticResourceRepository	  &staticResourceRepository,
		IStaticResourceReaderProvider &staticResourceReaderProvider
	);

	FindStaticResourceOutput execute(FindStaticResourceInput const &dtoInput);

  private:
	FindStaticResourceUseCase(FindStaticResourceUseCase const &src);
	FindStaticResourceUseCase &operator=(FindStaticResourceUseCase const &rhs);

	IStaticResourceRepository	  &_staticResourceRepository;
	IStaticResourceReaderProvider &_staticResourceReaderProvider;
};

#endif // FINDSTATICRESOURCEUSECASE_HPP