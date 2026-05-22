/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:12:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/22 20:08:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Handler.hpp"
#include "infrastructure/http/Context.hpp"

namespace http
{
	Handler::Handler(void)
	{}

	ITransferContext	*Handler::createClientContext(void)
	{
		return (new Context());
	}

	void	Handler::processClient(Client &client)
	{

	}


}
