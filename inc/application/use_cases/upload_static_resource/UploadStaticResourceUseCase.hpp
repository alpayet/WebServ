/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceUseCase.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADSTATICRESOURCEUSECASE_HPP
#define UPLOADSTATICRESOURCEUSECASE_HPP

class IStaticResourceRepository;
class UploadStaticResourceDto;

class UploadStaticResourceUseCase
{
  public:
	UploadStaticResourceUseCase(IStaticResourceRepository &staticFileRepository);

	void execute(UploadStaticResourceDto const &dto);

  private:
	UploadStaticResourceUseCase(UploadStaticResourceUseCase const &src);
	UploadStaticResourceUseCase &operator=(UploadStaticResourceUseCase const &rhs);

	IStaticResourceRepository &_staticFileRepository;
};

#endif // UPLOADSTATICRESOURCEUSECASE_HPP