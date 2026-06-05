/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UploadStaticResourceDto.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:28:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 20:42:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOADSTATICRESOURCEREQUESTDTO_HPP
#define UPLOADSTATICRESOURCEREQUESTDTO_HPP

#include <string>

class IDataSource;

struct UploadStaticResourceDto
{
	std::string	 target;
	IDataSource *dataSource;
};

#endif // UPLOADSTATICRESOURCEREQUESTDTO_HPP