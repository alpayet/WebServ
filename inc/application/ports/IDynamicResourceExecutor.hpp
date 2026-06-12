/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDynamicResourceExecutor.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:49:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:06:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDYNAMICRESOURCEEXECUTOR_HPP
#define IDYNAMICRESOURCEEXECUTOR_HPP

#include <map>
#include <string>

// TODO: faire herité CGI de cette interface
namespace app {
class IDynamicResourceExecutor
{
  public:
	virtual ~IDynamicResourceExecutor(void) {}

	virtual void execute(
		std::string const &storagePath, std::map<std::string, std::string> const &parameters
	) = 0;
};
} // namespace app

#endif // IDYNAMICRESOURCEEXECUTOR_HPP