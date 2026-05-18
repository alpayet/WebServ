/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestDto.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:02:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/07 19:52:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTDTO_HPP
# define HTTPREQUESTDTO_HPP

# include <string>
# include <map>

struct HttpRequestDto
{
	enum MethodType
	{
		httpGet,
		httpPost,
		httpDelete,
		unknown
	};

	MethodType							method;
	std::string							target;
	std::string							protocol;
	std::map<std::string, std::string>	headers;
};

#endif