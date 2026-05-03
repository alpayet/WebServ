/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestDto.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:02:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/03 18:16:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTDTO_HPP
# define REQUESTDTO_HPP

# include <string>
# include <map>

struct RequestDto
{
	// IRequest::MethodType				_method;
	std::string							_target;
	std::string							_protocol;
	std::map<std::string, std::string>	_headers;
};

#endif