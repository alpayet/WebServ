/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransfertHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:56:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 04:07:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITRANSFERTHANDLER_HPP
#define ITRANSFERTHANDLER_HPP

class ITransfertHandler
{
  public:
	virtual ~ITransfertHandler() {}

	virtual void createContext(unsigned int id) = 0;

	virtual bool push(unsigned int id, std::vector<char> &inputBuf) = 0;
	virtual bool pull(unsigned int id, std::vector<char> &outputBuf) = 0;
};

#endif // ITRANSFERTHANDLER_HPP