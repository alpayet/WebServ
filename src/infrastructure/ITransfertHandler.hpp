/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransfertHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:56:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:51:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITRANSFERTHANDLER_HPP
#define ITRANSFERTHANDLER_HPP

#include "server/applicative_protocol/IProtocol.hpp"

#include <vector>

struct Context;

class ITransfertHandler
{
  public:
	enum ProcessingStatus
	{
		needMoreData,
		complete
	};
	struct RequestStatus
	{
		enum Type
		{
			normal,
			timeOut
		};
	};
	struct StreamStatus
	{
		enum Type
		{
			normal,
			timeOut,
			endOfStream
		};
	};

  public:
	virtual ~ITransfertHandler() {}

	virtual void prepareContext(Context &context) = 0;

	virtual ITransfertHandler::ProcessingStatus
	pushRequest(Context &context, std::vector<char> const &inputBuf, RequestStatus::Type status) = 0;
	virtual ITransfertHandler::ProcessingStatus
	pushStream(Context &context, std::vector<char> const &streamBuf, StreamStatus::Type status) = 0;

	virtual std::vector<char> const &pull(Context &context) = 0;

	virtual bool isResponseComplete(Context &context) = 0;

	virtual void reset(Context &context) = 0;
};

#endif // ITRANSFERTHANDLER_HPP
