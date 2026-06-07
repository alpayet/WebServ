/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceUseCase.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:27:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

class DeleteStaticResourceInput;
class DeleteStaticResourceOutput;
class IStaticResourceRepository;

class DeleteStaticResourceUseCase
{
  public:
	DeleteStaticResourceUseCase(IStaticResourceRepository &staticResourceRepository);

	DeleteStaticResourceOutput execute(DeleteStaticResourceInput const &dtoInput);

  private:
	DeleteStaticResourceUseCase(DeleteStaticResourceUseCase const &src);
	DeleteStaticResourceUseCase &operator=(DeleteStaticResourceUseCase const &rhs);

	IStaticResourceRepository &_staticResourceRepository;
};

#endif // DELETESTATICRESOURCEUSECASE_HPP