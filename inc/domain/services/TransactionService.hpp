/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TransactionService.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:14:48 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/03 21:32:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSACTIONSERVICE_HPP
# define TRANSACTIONSERVICE_HPP

# include "domain/ports/IRequestInputPort.hpp"

class IResponseOutputPort;

class TransactionService : public IRequestInputPort
{
	public:
		TransactionService(IResponseOutputPort *responseOutputPort);

		virtual void	handle(RequestEntity const &requestDto);

		void	requestBuilder(void);

	private:
		IResponseOutputPort	*_responseOutputPort;
		ResponseDto			_responseDto;
};

#endif