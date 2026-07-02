/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IErrorPagesProvider.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 02:28:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 02:41:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPIERRORPAGESPROVIDER_HPP
#define HTTPIERRORPAGESPROVIDER_HPP

#include <map>
#include <string>

namespace http {
class IErrorPagesProvider
{
  public:
	virtual ~IErrorPagesProvider(void) {}

	virtual std::map<int, std::string> const &getErrPages(void) const = 0;
};
} // namespace http

#endif // HTTPIERRORPAGESPROVIDER_HPP