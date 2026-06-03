/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileUseCase.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/02 13:59:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADFILEUSECASE_HPP
#define UPLOADFILEUSECASE_HPP

class IConfigProvider;
class IStaticFileRepository;
class UploadFileDto;

class UploadFileUseCase
{
  public:
	UploadFileUseCase(IConfigProvider &configProvider, IStaticFileRepository &staticFileRepository);

	void execute(UploadFileDto const &dto);

  private:
	UploadFileUseCase(UploadFileUseCase const &src);
	UploadFileUseCase &operator=(UploadFileUseCase const &rhs);

	IConfigProvider		  &_configProvider;
	IStaticFileRepository &_staticFileRepository;
};

#endif // UPLOADFILEUSECASE_HPP