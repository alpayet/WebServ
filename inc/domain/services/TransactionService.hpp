/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TransactionService.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:14:48 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/05 18:43:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSACTIONSERVICE_HPP
# define TRANSACTIONSERVICE_HPP

# include "domain/ports/inbound/IRequestInputPort.hpp"
# include "domain/entities/RequestEntity.hpp"

class IResponseOutputPort;

class TransactionService : public IRequestInputPort
{
	public:
		TransactionService(IResponseOutputPort *responseOutputPort);
		virtual	~TransactionService(void) {}

		virtual void	handle(RequestEntity const &requestEntity);

	private:
		IResponseOutputPort	*_responseOutputPort;
};

#endif