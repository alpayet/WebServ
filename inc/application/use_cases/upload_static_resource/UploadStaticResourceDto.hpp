/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceDto.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:28:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:42:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADSTATICRESOURCEREQUESTDTO_HPP
#define UPLOADSTATICRESOURCEREQUESTDTO_HPP

#include <string>

struct UploadStaticResourceDto
{
	std::string temporaryFilePath;
	std::string target;
};

#endif // UPLOADSTATICRESOURCEREQUESTDTO_HPP