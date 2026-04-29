/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/29 19:20:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <vector>

class HttpTransaction;

class Client
{
	public:
		Client(void);
		Client(Client const &src);
		~Client(void);

		Client	&operator=(Client const &rhs);

	private:
		std::vector<char>	_readBuf;
		HttpTransaction		*_currentTransaction;
		int					_socketFd;
};


#endif