/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileUseCase.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 04:17:02 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADFILEUSECASE_HPP
#define UPLOADFILEUSECASE_HPP

class IConfigurationProvider;
class IFileRepository;
class UploadFileDto;

class UploadFileUseCase
{
  public:
	UploadFileUseCase(void);
	UploadFileUseCase(UploadFileUseCase const &src);
	~UploadFileUseCase(void);

	UploadFileUseCase &operator=(UploadFileUseCase const &rhs);

	void execute(UploadFileDto const &dto);

  private:
	IConfigurationProvider *_configurationProvider;
	IFileRepository		   *_fileRepository;
};

#endif // UPLOADFILEUSECASE_HPP