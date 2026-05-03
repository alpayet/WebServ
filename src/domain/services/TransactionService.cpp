/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TransactionService.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:31:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 00:33:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/services/TransactionService.hpp"
#include "domain/ports/IResponseOutputPort.hpp"
#include "domain/entities/RequestEntity.hpp"

TransactionService::TransactionService(IResponseOutputPort *responseOutputPort) :
	_responseOutputPort(responseOutputPort)
{}

void	TransactionService::handle(RequestDto const &requestDto)
{
	RequestEntity request;

	this->_responseOutputPort->present(this->_responseDto);
}