/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransfertHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:56:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 00:12:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITRANSFERTHANDLER_HPP
#define ITRANSFERTHANDLER_HPP

#include <vector>

class ITransfertHandler
{
  public:
	enum ProcessingStatus
	{
		needMoreData,
		complete
	};
	enum RequestStatus
	{
		normal,
		timeOut
	};
	enum StreamStatus
	{
		normal,
		timeOut,
		endOfStream
	};

  public:
	virtual ~ITransfertHandler() {}

	virtual void prepareContext(unsigned int id) = 0;

	virtual ProcessingStatus
	pushRequest(unsigned int id, std::vector<char> const &inputBuf, RequestStatus status) = 0;
	virtual ProcessingStatus
	pushStream(unsigned int id, std::vector<char> const &streamBuf, StreamStatus status) = 0;

	virtual std::vector<char> const &pull(unsigned int id) = 0;

	virtual bool isResponseComplete(unsigned int id) = 0;

	virtual void reset(unsigned int id) = 0;
};

#endif // ITRANSFERTHANDLER_HPP