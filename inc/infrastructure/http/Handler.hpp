/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:15:09 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/24 23:09:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLER_HPP
#define HTTPHANDLER_HPP

#include "infrastructure/ITransfertHandler.hpp"

namespace http
{
	class Handler : public ITransfertHandler
	{
	  public:
		Handler(void);
		virtual ~Handler(void) {}

		virtual ITransferContext *createClientContext(void);

		virtual void processClient(Client &client);

	  private:
		Handler(Handler const &src) {}
		Handler &operator=(Handler const &rhs) {}
	};
} // namespace http

#endif // HTTPHANDLER_HPP