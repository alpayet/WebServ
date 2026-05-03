/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestEntity.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 20:17:39 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/03 21:32:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <map>

class RequestEntity
{
	public:
		RequestEntity(std::string const &target,
			std::string const &protocol, std::map<std::string, std::string> const &headers);

	private:
		std::string							_target;
		std::string							_protocol;
		std::map<std::string, std::string>	_headers;
};

#endif