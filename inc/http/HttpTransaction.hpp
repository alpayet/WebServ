/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpTransaction.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:14:48 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/29 22:13:17 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPTRANSACTION_HPP
# define HTTPTRANSACTION_HPP

# include "HttpRequestParser.hpp"

class IRequest;

class HttpTransaction
{
	public:
		HttpTransaction(void);
		HttpTransaction(HttpTransaction const &src);
		~HttpTransaction(void);

		HttpTransaction	&operator=(HttpTransaction const &rhs);

		void	onDataReceived(std::vector<char> const &readBuf);
		void	requestBuilder(void);

	private:
		IRequest			*_request;
		HttpRequestParser	_requestParser;
};

#endif