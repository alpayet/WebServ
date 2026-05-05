/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestDto.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:02:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/05 17:29:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTDTO_HPP
# define REQUESTDTO_HPP

# include <string>
# include <map>

struct RequestDto
{
	// IRequest::MethodType				_method;
	std::string							target;
	std::string							protocol;
	std::map<std::string, std::string>	headers;
};

#endif