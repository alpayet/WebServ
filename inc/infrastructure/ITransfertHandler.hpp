/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransfertHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:56:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/24 04:45:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITRANSFERTHANDLER_HPP
#define ITRANSFERTHANDLER_HPP

class ITransfertHandler
{
  public:
	virtual ~ITransfertHandler() {}

	virtual void createContext(unsigned int id) = 0;

	virtual void			  push(unsigned int id, std::vector<char> &inputBuf) = 0;
	virtual std::vector<char> pull(unsigned int id) = 0;

	virtual bool isRequestComplete(unsigned int id) = 0;
	virtual bool isResponseComplete(unsigned int id) = 0;
};

#endif // ITRANSFERTHANDLER_HPP