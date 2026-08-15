/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IErrorPagesProvider.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 02:28:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:11:50 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPIERRORPAGESPROVIDER_HPP
#define HTTPIERRORPAGESPROVIDER_HPP

#include "application/ports/SystemResourceInfo.hpp"
#include <map>
#include <string>

namespace webserv {
namespace http {
class IErrorPagesProvider
{
  public:
	virtual ~IErrorPagesProvider(void) {}

	virtual std::map<int, std::string> const &getErrPages(void) const = 0;
	virtual app::SystemResourceInfo			  locateErrorPage(std::string const &uri) const = 0;
};
} // namespace http
} // namespace webserv

#endif // HTTPIERRORPAGESPROVIDER_HPP