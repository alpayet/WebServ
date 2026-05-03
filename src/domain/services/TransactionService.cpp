/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TransactionService.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:31:52 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/03 21:32:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/services/TransactionService.hpp"
#include "domain/ports/IResponseOutputPort.hpp"
#include "domain/entities/Request.hpp"

TransactionService::TransactionService(IResponseOutputPort *responseOutputPort) :
	_responseOutputPort(responseOutputPort)
{}

void	TransactionService::handle(RequestDto const &requestDto)
{
	RequestEntity request;

	this->_responseOutputPort->present(this->_responseDto);
}