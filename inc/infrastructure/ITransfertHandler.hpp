/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransfertHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:56:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/22 18:04:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITRANSFERTHANDLER_HPP
# define ITRANSFERTHANDLER_HPP

#include "infrastructure/Client.hpp"

class ITransferContext;

class ITransfertHandler
{
	public:
		virtual ~ITransfertHandler() {}

		virtual ITransferContext*	createClientContext() = 0;

		virtual void	processClient(Client &client) = 0;
};

#endif