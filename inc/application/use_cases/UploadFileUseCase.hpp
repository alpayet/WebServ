/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileUseCase.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/01 17:31:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADFILEUSECASE_HPP
#define UPLOADFILEUSECASE_HPP

class IConfigProvider;
class IFileRepository;
class UploadFileDto;

class UploadFileUseCase
{
  public:
	UploadFileUseCase(IConfigProvider &configProvider, IFileRepository &fileRepository);

	void execute(UploadFileDto const &dto);

  private:
	UploadFileUseCase(UploadFileUseCase const &src);
	UploadFileUseCase &operator=(UploadFileUseCase const &rhs);

	IConfigProvider &_configProvider;
	IFileRepository &_fileRepository;
};

#endif // UPLOADFILEUSECASE_HPP