/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:43 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/24 23:10:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>

class ITransferContext;

class Client
{
  public:
	Client(void);
	Client(Client const &src);
	~Client(void);

	Client &operator=(Client const &rhs);

  private:
	int				  _socketFd;
	std::vector<char> _readBuf;
	ITransferContext *_transfertContext;
};

#endif // CLIENT_HPP