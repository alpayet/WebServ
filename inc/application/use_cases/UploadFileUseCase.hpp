/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileUseCase.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/18 15:25:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADFILEUSECASE_HPP
# define UPLOADFILEUSECASE_HPP

class UploadFileUseCase
{
	public:
		UploadFileUseCase(void);
		UploadFileUseCase(UploadFileUseCase const &src);
		~UploadFileUseCase(void);

		UploadFileUseCase	&operator=(UploadFileUseCase const &rhs);

	private:

};

#endif