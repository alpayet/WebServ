/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TransactionService.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:31:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 18:13:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/services/TransactionService.hpp"
#include "domain/ports/outbound/IResponseOutputPort.hpp"
#include "domain/entities/RequestEntity.hpp"

TransactionService::TransactionService(IResponseOutputPort *responseOutputPort) :
	_responseOutputPort(responseOutputPort)
{}

void	TransactionService::handle(RequestEntity const &requestEntity)
{
	// this->_responseOutputPort->present(this);
}