/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadFileDto.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:28:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 03:40:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADFILEREQUESTDTO_HPP
#define UPLOADFILEREQUESTDTO_HPP

#include <string>

struct UploadFileDto
{
	std::string temporaryFilePath;
	std::string target;
};

#endif // UPLOADFILEREQUESTDTO_HPP