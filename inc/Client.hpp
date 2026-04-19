/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/19 20:35:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "IRequest.hpp"
# include <vector>

class IRequest;

class Client
{
	public:
		Client(void);
		Client(Client const &src);
		~Client(void);

		Client	&operator=(Client const &rhs);

	private:
		std::vector<char>	_readBuf;
		IRequest			*_request;
		int					_socketFd;
};

#endif