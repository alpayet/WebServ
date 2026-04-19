/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:31:07 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/19 22:57:24 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMESSAGE_HPP
# define HTTPMESSAGE_HPP

# include <map>
# include <string>

class HttpMessage
{
	public:
		HttpMessage(void);
		HttpMessage(HttpMessage const &src);
		virtual ~HttpMessage(void);

		HttpMessage	&operator=(HttpMessage const &rhs);

	protected:
		std::map<std::string, std::string> _headers;
		//body
};

#endif